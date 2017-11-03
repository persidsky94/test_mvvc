#ifndef CIRCLEREDACTOR_H
#define CIRCLEREDACTOR_H

#include <QWidget>
#include <circleparams.h>

namespace Ui {
class circleRedactor;
}

class circleRedactor : public QWidget
{
	Q_OBJECT

public:
	explicit circleRedactor(QWidget *parent = 0);
	~circleRedactor();
	void initWithParams(circleParams params);

signals: //to item
	void setParams(circleParams params);

private:
	Ui::circleRedactor *ui;

	circleParams constructParams();

//slots from item
	void updateParams(circleParams params);
//slots from ui
	void on_setButton_clicked();
};

#endif // CIRCLEREDACTOR_H
