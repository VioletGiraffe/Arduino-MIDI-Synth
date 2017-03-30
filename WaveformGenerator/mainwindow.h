#pragma once

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>

#include <cstdint>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void generateWaveformSourceCode();

	void generateWaveform();
	void updateWaveformGraph();

	uint32_t numSamples() const;
	float amplitude() const;
	bool signedSamples() const;

private:
	Ui::MainWindow *ui;

	std::vector<float> _samples;

	QtCharts::QChart _chart;
	QtCharts::QChartView* _chartView = nullptr;
	QtCharts::QLineSeries* _series = nullptr;
};

