#ifndef SQUAREREDACTOR_H
#define SQUAREREDACTOR_H

#include <QWidget>
#include <squareparams.h>

namespace Ui {
class squareRedactor;
}

class squareRedactor : public QWidget
{
	Q_OBJECT

public:
	explicit squareRedactor(QWidget *parent = 0);
	~squareRedactor();
	void initWithParams(squareParams params);

signals: //to item
	void setParams(squareParams params);

private:
	Ui::squareRedactor *ui;

	squareParams constructParams();

//slots from item
	void updateParams(squareParams params);
//slots from ui
	void on_setButton_clicked();
};

#endif // SQUAREREDACTOR_H
