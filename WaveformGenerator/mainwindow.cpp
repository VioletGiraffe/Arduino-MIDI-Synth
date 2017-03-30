#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generator.h"

#include <QValueAxis>

#include <iterator>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

// Graph setup
	_chartView = new QChartView(&_chart);
	auto chartLayout = new QHBoxLayout;
	chartLayout->addWidget(_chartView);
	ui->chartWidget->setLayout(chartLayout);

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
	connect(ui->waveform, (void (QComboBox::*)(int))&QComboBox::currentIndexChanged, this, [this](int){
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

	connect(ui->generate, &QPushButton::clicked, this, &MainWindow::generateWaveformSourceCode);

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

}

void MainWindow::generateWaveform()
{
	_samples = Generator::generateSine(numSamples(), amplitude(), signedSamples());
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
