#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sourcecodedialog/generatedsourcecodedialog.h"
#include "generators/sinegenerator.h"
#include "generators/squaregenerator.h"
#include "generators/trianglegenerator.h"

#include <QStringBuilder>
#include <QValueAxis>

#include <iterator>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

// Graph setup
	ui->chartWidget->setChart(&_chart);

	_series = new QLineSeries;
	_chart.addSeries(_series);

	auto axisX = new QValueAxis;
	_chart.setAxisX(axisX, _series);
	auto axisY = new QValueAxis;
	axisY->setTitleText("Amplitude");
	_chart.setAxisY(axisY, _series);
	_chart.legend()->hide();

// Live UI
	connect(ui->numSamples, (void (QSpinBox::*)(int))&QSpinBox::valueChanged, this, [this](int){
		setupGraphXAxis();
		generateWaveform();
	});
	connect(ui->waveform, (void (QComboBox::*)(int))&QComboBox::currentIndexChanged, this, [this](int waveformIndex){
		ui->extraParameter->setValue(_generators[waveformIndex]->extraParameter());
		ui->extraParameterName->setText(_generators[waveformIndex]->extraParameterName());

		generateWaveform();
	});
	connect(ui->amplitude, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, [this](double){
		setupGraphYAxis();
		generateWaveform();
	});
	connect(ui->signedSamples, &QCheckBox::toggled, this, [this](bool){
		setupGraphYAxis();
		generateWaveform();
	});
	connect(ui->extraParameter, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, [this](double value){
		currentWaveformGenerator()->setExtraParameter((float)value);
		generateWaveform();
	});

	connect(ui->generate, &QPushButton::clicked, this, &MainWindow::generateWaveformSourceCode);

// Generators
	_generators.emplace_back(std::make_unique<SineGenerator>());
	_generators.emplace_back(std::make_unique<SquareGenerator>());
	_generators.emplace_back(std::make_unique<TriangleGenerator>());

// Final UI initialization
	for (const auto& gen: _generators)
		ui->waveform->addItem(gen->name());

	setupGraphXAxis();
	setupGraphYAxis();

	generateWaveform();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::generateWaveformSourceCode()
{
	QString sourceCode = ui->type->text() + " waveform[] = {\n";
	for (const float sample: _samples)
	{
		QString sampleText = QString::number((double)sample, 'g', 20);
		if (!sampleText.contains('.') && !sampleText.contains('e'))
			sampleText += ".0";

		sourceCode += '\t' % sampleText % "f,\n";
	}

	if (!_samples.empty())
		sourceCode.chop(2); // Remove extra ",\n" after the last item

	sourceCode += "\n};";

	GeneratedSourceCodeDialog sourceCodeView;
	sourceCodeView.setCode(sourceCode);
	sourceCodeView.exec();
}

void MainWindow::generateWaveform()
{
	_samples = currentWaveformGenerator()->generate(numSamples(), amplitude(), signedSamples());
	updateWaveformGraph();
}

void MainWindow::updateWaveformGraph()
{
	QVector<QPointF> points;
	points.reserve((int)_samples.size());
	for (size_t i = 0; i < _samples.size(); ++i)
	{
		QPointF point((float)i, _samples[i]);
		points.push_back(point);
	}

	_series->replace(points);
}

uint32_t MainWindow::numSamples() const
{
	return (uint32_t)ui->numSamples->value();
}

float MainWindow::amplitude() const
{
	return (float)ui->amplitude->value();
}

bool MainWindow::signedSamples() const
{
	return ui->signedSamples->isChecked();
}

void MainWindow::setupGraphXAxis()
{
	_chart.axisX()->setRange(0, numSamples());
}

void MainWindow::setupGraphYAxis()
{
	_chart.axisY()->setRange(signedSamples() ? -amplitude() : 0, signedSamples() ? amplitude() : 2.0 * amplitude());
}

WaveformGenerator*MainWindow::currentWaveformGenerator() const
{
	return _generators[ui->waveform->currentIndex()].get();
}
