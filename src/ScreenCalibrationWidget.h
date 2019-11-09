#ifndef SCREENCALIBRATIONWIDGET_H
#define SCREENCALIBRATIONWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QResizeEvent>
#include <QMenu>
#include <QSignalMapper>

class ScreenCalibrationWidget : public QWidget
{
	Q_OBJECT
public:
	ScreenCalibrationWidget(QWidget * parent = nullptr);
	virtual ~ScreenCalibrationWidget() = default;

	double dpi() const;

public slots:
	void setDpi(const double dpi);
	void setUnit(const int unitIdx);

signals:
	void dpiChanged(double dpi);

protected slots:
	void recalculateSizes();
	void retranslate();
	void repositionSpinBox();

protected:
	virtual void paintEvent(QPaintEvent * event);
	virtual void resizeEvent(QResizeEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);
	virtual void changeEvent(QEvent * event);
	virtual void contextMenuEvent(QContextMenuEvent * event);
	virtual bool eventFilter(QObject * object, QEvent * event);


	QDoubleSpinBox * _sbDPI;
	QRect _rulerRect;
	unsigned int _majorTickHeight{20}, _mediumTickHeight{10}, _minorTickHeight{5}, _paperTickHeight{40};
	QMenu _contextMenu;
	QActionGroup _contextMenuActionGroup;
	QSignalMapper _unitSignalMapper;

	struct unit {
		QString label;
		float unitsPerInch;
	};
	QList<unit> _units;

	struct paperSize {
		QString name;
		QSizeF size; // specify in inch
		QColor col; // for display
		Qt::Alignment alignment;
		bool visible;
	};
	QList<paperSize> _paperSizes;
	unsigned int _curUnit;
	int _hSpace{0};

	QPoint _mouseDownPos;
	float _mouseDownInches{0};
	bool _isDragging{false};
};

#endif // SCREENCALIBRATIONWIDGET_H
