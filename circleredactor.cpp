#include "circleredactor.h"
#include "ui_circleredactor.h"

circleRedactor::circleRedactor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::circleRedactor)
{
	ui->setupUi(this);
	QObject::connect(this->ui->setButton, &QPushButton::clicked, this, &circleRedactor::on_setButton_clicked);
}

circleRedactor::~circleRedactor()
{
	delete ui;
}

circleParams circleRedactor::constructParams()
{
	circleParams params;
	params.name = this->ui->nameLine->text();
	params.x = this->ui->xBox->value();
	params.y = this->ui->yBox->value();
	params.radius = this->ui->radiusBox->value();
	params.density = this->ui->densityBox->value();
	params.originality = this->ui->originalityBox->value();
	return params;
}

void circleRedactor::initWithParams(circleParams params)
{
	updateParams(params);
}

void circleRedactor::updateParams(circleParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->xBox->setValue(params.x);
	this->ui->yBox->setValue(params.y);
	this->ui->radiusBox->setValue(params.radius);
	this->ui->densityBox->setValue(params.density);
	this->ui->originalityBox->setValue(params.originality);
}

void circleRedactor::on_setButton_clicked()
{
	emit setParams(constructParams());
}
