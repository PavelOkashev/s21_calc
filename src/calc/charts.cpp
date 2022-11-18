#include "charts.h"
#include "ui_charts.h"

charts::charts(QWidget *parent) : QWidget(parent), ui(new Ui::charts) {
  ui->setupUi(this);

  this->interval = 10;
  ui->widget->xAxis->setRange(-100, 100);
  ui->widget->yAxis->setRange(-100, 100);
  ui->show_interval->setText("");
  ui->show_min->setText("");
  ui->show_max->setText("");

  connect(ui->zero, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(all_numbers_func_ch()));

  connect(ui->min_x, SIGNAL(clicked()), this, SLOT(params()));
  connect(ui->max_x, SIGNAL(clicked()), this, SLOT(params()));
  connect(ui->interval_x, SIGNAL(clicked()), this, SLOT(params()));
}

charts::~charts() { delete ui; }

void charts::expfc(const QString &text) { this->expresssion = text; }

void charts::all_numbers_func_ch() {
  QPushButton *obj = (QPushButton *)sender();
  if (ui->min_x->isChecked()) {
    if (ui->show_min->text().contains("incorrect")) {
      ui->show_min->setText("");
    }
    ui->show_min->setText(ui->show_min->text().append(obj->text()));
  } else if (ui->max_x->isChecked()) {
    if (ui->show_max->text().contains("incorrect")) {
      ui->show_max->setText("");
    }
    ui->show_max->setText(ui->show_max->text().append(obj->text()));
  } else if (ui->interval_x->isChecked()) {
    if (ui->show_max->text().contains("incorrect")) {
      ui->show_max->setText("");
    }
    ui->show_interval->setText(ui->show_interval->text().append(obj->text()));
  }
}

void charts::on_dot_clicked() {
  if (ui->min_x->isChecked() && !ui->show_min->text().contains(".") &&
      !ui->show_min->text().isEmpty()) {
    if (ui->show_min->text().contains("incorrect")) {
      ui->show_min->setText("");
    }
    ui->show_min->setText(ui->show_min->text().append("."));
  } else if (ui->max_x->isChecked() && !ui->show_max->text().contains(".") &&
             !ui->show_max->text().isEmpty()) {
    if (ui->show_max->text().contains("incorrect")) {
      ui->show_max->setText("");
    }
    ui->show_max->setText(ui->show_max->text().append("."));
  } else if (ui->interval_x->isChecked() &&
             !ui->show_interval->text().contains(".") &&
             !ui->show_interval->text().isEmpty()) {
    if (ui->show_max->text().contains("incorrect")) {
      ui->show_max->setText("");
    }
    ui->show_interval->setText(ui->show_interval->text().append("."));
  }
}

void charts::on_del_clicked() {
  if (ui->min_x->isChecked()) {
    ui->show_min->setText("");
  } else if (ui->max_x->isChecked()) {
    ui->show_max->setText("");
  } else if (ui->interval_x->isChecked()) {
    ui->show_interval->setText("");
  }
}

void charts::min_valid(QString a) {
  if (!a.isEmpty() && !a.endsWith(QChar('.')) && !a.contains("incorrect")) {
    this->xMin = ui->show_min->text().toDouble();
    if (this->xMin < 1000000 && this->xMin > -1000000) {
      this->min_v = true;
    } else {
      ui->show_min->setText("incorrect");
    }
  } else {
    ui->show_min->setText("incorrect");
  }
}

void charts::max_valid(QString a) {
  if (!a.isEmpty() && !a.endsWith(QChar('.')) && !a.contains("incorrect")) {
    this->xMax = ui->show_max->text().toDouble();
    if (this->xMax < 1000000 && this->xMax > -1000000 &&
        this->xMin < this->xMax) {
      this->max_v = true;
    } else {
      ui->show_max->setText("incorrect");
    }
  } else {
    ui->show_max->setText("incorrect");
  }
}

void charts::interval_valid(QString a) {
  if (!a.isEmpty() && !a.endsWith(QChar('.')) && !a.contains("incorrect")) {
    this->interval = ui->show_interval->text().toDouble();
    if (((this->xMax - this->xMin) / (this->interval + 2)) > 0) {
      this->interval_v = true;
    } else {
      ui->show_interval->setText("incorrect");
    }
  } else {
    ui->show_interval->setText("incorrect");
  }
}

void charts::on_build_clicked() {
  ui->widget->clearGraphs();
  this->y.clear();
  this->x.clear();
  min_valid(ui->show_min->text());
  if (this->min_v) {
    max_valid(ui->show_max->text());
    if (this->max_v) {
      interval_valid(ui->show_interval->text());
    }
  }
  if (this->min_v && this->max_v && this->interval_v) {
    while (this->xMin <= this->xMax) {
      QString ln = this->expresssion;
      if (this->xMin < 0) {
        QString a = "";
        a = a + "(";
        a = a + QString::number(this->xMin, 'f', 3);
        a = a + ")";
        ln.replace("x", a);
      } else {
        ln.replace("x", QString::number(this->xMin));
      }
      qDebug() << ln;
      std::string std_ln = ln.toStdString();
      const char *c_line = std_ln.c_str();
      x.push_back(this->xMin);
      double a = (double)standart_calc((char *)c_line);
      y.push_back(a);
      this->xMin += this->interval;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(this->x, this->y);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    //       clean_build();
  } else {
    clean_build();
  }
}

void charts::clean_build() {
  this->min_v = false;
  this->max_v = false;
  this->interval_v = false;
  this->xMin = 0;
  this->xMax = 0;
  this->interval = 0;
  ui->widget->clearGraphs();
  this->y.clear();
  this->x.clear();
}

void charts::on_minus_clicked() {
  if (ui->min_x->isChecked() && ui->show_min->text().isEmpty()) {
    ui->show_min->setText(ui->show_min->text().append("-"));
  } else if (ui->max_x->isChecked() && ui->show_max->text().isEmpty()) {
    ui->show_max->setText(ui->show_max->text().append("-"));
  } else if (ui->interval_x->isChecked() &&
             ui->show_interval->text().isEmpty()) {
    ui->show_interval->setText(ui->show_interval->text().append("-"));
  }
}
