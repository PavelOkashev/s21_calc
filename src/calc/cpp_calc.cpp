#include "cpp_calc.h"
#include "ui_cpp_calc.h"

cpp_calc::cpp_calc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::cpp_calc) {
  ui->setupUi(this);

  connect(ui->zero, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(all_numbers_func()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(all_numbers_func()));

  connect(ui->mult, SIGNAL(clicked()), this, SLOT(binari_func()));
  connect(ui->degree, SIGNAL(clicked()), this, SLOT(binari_func()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(binari_func()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(binari_func()));

  connect(ui->minus, SIGNAL(clicked()), this, SLOT(minus_and_plus_func()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(minus_and_plus_func()));

  connect(ui->l_br, SIGNAL(clicked()), this, SLOT(br_func()));
  connect(ui->r_br, SIGNAL(clicked()), this, SLOT(br_func()));

  connect(ui->sin, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(unari_func()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(unari_func()));
}

cpp_calc::~cpp_calc() { delete ui; }

void cpp_calc::all_numbers_func() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 255) {
    if (!ui->output->text().endsWith(QChar(')')) &&
        !ui->output->text().endsWith(QChar('x'))) {
      QPushButton *obj = (QPushButton *)sender();
      ui->output->setText(ui->output->text().append(obj->text()));
    }
  }
}

bool cpp_calc::num_valid(QString a) {

  bool res = false;
  char num = '0';
  while (num <= '9' && !res) {
    res = a.endsWith(QChar(num));
    num += 1;
  }
  return res;
}

void cpp_calc::on_dot_clicked() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 255) {
    if (num_valid(ui->output->text()) && !this->is_dot) {
      this->is_dot = true;
      ui->output->setText(ui->output->text().append('.'));
    }
  }
}

void cpp_calc::on_del_clicked() {
  this->is_dot = false;
  this->eq = false;
  this->b_count = 0;
  ui->output->setText("");
}

void cpp_calc::binari_func() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 255) {
    if (ui->output->text().endsWith(QChar(')')) ||
        num_valid(ui->output->text()) ||
        ui->output->text().endsWith(QChar('x'))) {
      this->is_dot = false;
      QPushButton *obj = (QPushButton *)sender();
      ui->output->setText(ui->output->text().append(obj->text()));
    }
  }
}

void cpp_calc::minus_and_plus_func() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 255 &&
      !ui->output->text().endsWith(QChar('.'))) {
    QPushButton *obj = (QPushButton *)sender();
    if (ui->output->text().endsWith(QChar(')')) ||
        num_valid(ui->output->text()) ||
        ui->output->text().endsWith(QChar('x'))) {
      this->is_dot = false;
      ui->output->setText(ui->output->text().append(obj->text()));
    } else {
      ui->output->setText(ui->output->text().append(QChar('(')));
      this->b_count++;
      ui->output->setText(ui->output->text().append(obj->text()));
    }
  }
}

void cpp_calc::br_func() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 255 &&
      !ui->output->text().endsWith(QChar('.'))) {
    QPushButton *obj = (QPushButton *)sender();
    if (obj->text().endsWith(QChar('('))) {
      if (!ui->output->text().endsWith(QChar(')')) &&
          !ui->output->text().endsWith(QChar('x')) &&
          !num_valid(ui->output->text())) {
        this->b_count++;
        ui->output->setText(ui->output->text().append(obj->text()));
      }
    } else {
      if ((ui->output->text().endsWith(QChar(')')) ||
           ui->output->text().endsWith(QChar('x')) ||
           num_valid(ui->output->text())) &&
          this->b_count) {
        this->b_count--;
        ui->output->setText(ui->output->text().append(obj->text()));
      }
    }
  }
}

void cpp_calc::unari_func() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 252 &&
      !ui->output->text().endsWith(QChar('.'))) {
    if (!ui->output->text().endsWith(QChar('x')) &&
        !num_valid(ui->output->text()) &&
        !ui->output->text().endsWith(QChar(')'))) {
      QPushButton *obj = (QPushButton *)sender();
      ui->output->setText(ui->output->text().append(obj->text()));
      ui->output->setText(ui->output->text().append(QChar('(')));
      this->b_count++;
    }
  }
}

void cpp_calc::on_num_x_clicked() {
  if (this->eq) {
    on_del_clicked();
  }
  if (ui->output->text().size() < 255 &&
      !ui->output->text().endsWith(QChar('.'))) {
    if (!ui->output->text().endsWith(QChar('x')) &&
        !num_valid(ui->output->text()) &&
        !ui->output->text().endsWith(QChar(')'))) {
      QPushButton *obj = (QPushButton *)sender();
      ui->output->setText(ui->output->text().append(obj->text()));
    }
  }
}

void cpp_calc::on_eq_clicked() {
  if (!this->b_count && (ui->output->text().endsWith(QChar(')')) ||
                         ui->output->text().endsWith(QChar('x')) ||
                         num_valid(ui->output->text()))) {
    this->eq = true;
    QString ln = ui->output->text();
    ln.replace("asin", "S");
    ln.replace("acos", "C");
    ln.replace("atan", "T");
    ln.replace("sin", "s");
    ln.replace("cos", "c");
    ln.replace("tan", "t");
    ln.replace("log", "L");
    ln.replace("ln", "l");
    ln.replace("sqrt", "q");
    ln.replace("mod", "m");
    if (ui->output->text().contains(QChar('x'))) {
      chart = new charts();
      connect(this, SIGNAL(ewx(const QString &)), chart,
              SLOT(expfc(const QString &)));
      emit ewx(ln);
      chart->show();
    } else {
      std::string std_ln = ln.toStdString();
      const char *c_line = std_ln.c_str();
      long double res = standart_calc((char *)c_line);
      QString qline = QString::number((double)res, 'f', 7);
      ui->output->setText(qline);
    }
  }
}

void cpp_calc::on_credit_triggered() {
  credit_calc = new credit();
  credit_calc->show();
}

void cpp_calc::on_deposit_triggered() {
  deposit_calc = new deposit();
  deposit_calc->show();
}
