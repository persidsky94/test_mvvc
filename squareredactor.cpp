#include "squareredactor.h"
#include "ui_squareredactor.h"

squareRedactor::squareRedactor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::squareRedactor)
{
	ui->setupUi(this);
	QObject::connect(this->ui->setButton, &QPushButton::clicked, this, &squareRedactor::on_setButton_clicked);
}

squareRedactor::~squareRedactor()
{
	delete ui;
}

squareParams squareRedactor::constructParams()
{
	squareParams params;
	params.name = this->ui->nameLine->text();
	params.x = this->ui->xBox->value();
	params.y = this->ui->yBox->value();
	params.width = this->ui->widthBox->value();
	params.density = this->ui->densityBox->value();
	return params;
}

void squareRedactor::initWithParams(squareParams params)
{
	updateParams(params);
}

void squareRedactor::updateParams(squareParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->xBox->setValue(params.x);
	this->ui->yBox->setValue(params.y);
	this->ui->widthBox->setValue(params.width);
	this->ui->densityBox->setValue(params.density);
}

void squareRedactor::on_setButton_clicked()
{
	emit setParams(constructParams());
}
