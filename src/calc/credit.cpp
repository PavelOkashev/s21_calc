#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);

  ui->show_sum->setText("");
  ui->show_rate->setText("");
  ui->show_term->setText("");

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
}

credit::~credit() { delete ui; }

void credit::all_numbers_func_ch() {
  QPushButton *obj = (QPushButton *)sender();
  if (ui->sum->isChecked()) {
    if (ui->show_sum->text().contains("incorrect")) {
      ui->show_sum->setText("");
    }
    ui->show_sum->setText(ui->show_sum->text().append(obj->text()));
  } else if (ui->rate->isChecked()) {
    if (ui->show_rate->text().contains("incorrect")) {
      ui->show_rate->setText("");
    }
    ui->show_rate->setText(ui->show_rate->text().append(obj->text()));
  } else if (ui->term->isChecked()) {
    if (ui->show_term->text().contains("incorrect")) {
      ui->show_term->setText("");
    }
    ui->show_term->setText(ui->show_term->text().append(obj->text()));
  }
}

void credit::on_dot_clicked() {
  if (ui->sum->isChecked() && !ui->show_sum->text().contains(".") &&
      !ui->show_sum->text().isEmpty()) {
    if (ui->show_sum->text().contains("incorrect")) {
      ui->show_sum->setText("");
    }
    ui->show_sum->setText(ui->show_sum->text().append("."));
  } else if (ui->rate->isChecked() && !ui->show_rate->text().contains(".") &&
             !ui->show_rate->text().isEmpty()) {
    if (ui->show_rate->text().contains("incorrect")) {
      ui->show_rate->setText("");
    }
    ui->show_rate->setText(ui->show_rate->text().append("."));
  }
}

void credit::on_del_clicked() {
  if (ui->sum->isChecked()) {
    ui->show_sum->setText("");
  } else if (ui->rate->isChecked()) {
    ui->show_rate->setText("");
  } else if (ui->term->isChecked()) {
    ui->show_term->setText("");
  }
}

void credit::on_type_clicked() {
  if (!this->type) {
    this->type = true;
    ui->type->setText("different");
  } else {
    this->type = false;
    ui->type->setText("annuity");
  }
}

bool credit::eqils_valid(QWidget *a) {
  QLabel *b = (QLabel *)a;
  bool res = false;
  if (!b->text().isEmpty() && !b->text().endsWith(".") &&
      !b->text().contains("incorrect")) {
    res = true;
  } else {
    b->setText("incorrect");
  }
  return res;
}

void credit::on_calculate_clicked() {
  if (eqils_valid(ui->show_sum) && eqils_valid(ui->show_rate) &&
      eqils_valid(ui->show_term)) {
    if (!this->type) {
      double sum = ui->show_sum->text().toDouble();
      double term = ui->show_term->text().toDouble();
      double mount_proc = (ui->show_rate->text().toDouble() / 12) / 100;
      double coof_anuitet = (mount_proc * pow((1 + mount_proc), term)) /
                            (pow((1 + mount_proc), term) - 1);
      double mount_pay = round(sum * coof_anuitet);
      double tp = mount_pay * term;
      ui->show_mp->setText(QString::number(mount_pay));
      ui->show_tp->setText(QString::number(tp));
      ui->show_pp->setText(QString::number(round(tp - sum)));
    } else {
      double sum = ui->show_sum->text().toDouble();
      double term = ui->show_term->text().toDouble();
      double rate = (ui->show_rate->text().toDouble() / 12) / 100;
      double all_pay = 0;
      ui->show_mp->setText(QString::number(round(sum / term + sum * rate)));
      while (sum > 0) {
        all_pay += sum * rate;
        sum -= sum / term;
        term--;
      }
      ui->show_pp->setText(QString::number(round(all_pay)));
      ui->show_tp->setText(
          QString::number(round(ui->show_sum->text().toDouble() + all_pay)));
    }
  }
}
