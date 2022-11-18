#include "deposit.h"
#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QWidget(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
  ui->show_term->setText("");
  ui->show_percent->setText("");
  ui->show_tax->setText("");
  ui->show_deposit_amount->setText("");

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

  connect(ui->add_adding, &QPushButton::clicked, [this]() {
    add_element_list(&this->list_add, ui->dynamic_vert_layout_add);
  });
  connect(ui->add_debited, &QPushButton::clicked, [this]() {
    add_element_list(&this->list_deb, ui->dynamic_vert_layout_deb);
  });

  connect(ui->dell_adding, &QPushButton::clicked,
          [this]() { rm_element_list(&this->list_add); });
  connect(ui->dell_debiting, &QPushButton::clicked,
          [this]() { rm_element_list(&this->list_deb); });
}

deposit::~deposit() { delete ui; }

bool deposit::checked_list(QList<QLayout *> *list, QString text) {
  bool res = false;
  for (QList<QLayout *>::Iterator it = list->begin(); it != list->end(); it++) {
    QLayout *a = *it;
    QRadioButton *b = (QRadioButton *)a->itemAt(0)->widget();
    if (b->isChecked() && !text.contains(".")) {
      add_text(b, text, 1);
      res = true;
      break;
    } else if (b->isChecked() && text.contains(".")) {
      if (!b->text().contains(text) && !b->text().isEmpty()) {
        add_text(b, text, 1);
        res = true;
        break;
      }
    }
  }
  return res;
}

bool deposit::checked_list(QList<QLayout *> *list) {
  bool res = false;
  for (QList<QLayout *>::Iterator it = list->begin(); it != list->end(); it++) {
    QLayout *a = *it;
    QRadioButton *b = (QRadioButton *)a->itemAt(0)->widget();
    if (b->isChecked()) {
      b->setText("");
      res = true;
      break;
    }
  }
  return res;
}

void deposit::checked_list(QList<QLayout *> *list, bool *valid) {
  for (QList<QLayout *>::Iterator it = list->begin(); it != list->end(); it++) {
    QLayout *a = *it;
    QRadioButton *b = (QRadioButton *)a->itemAt(0)->widget();
    if (b->text().isEmpty() || b->text().endsWith(".") ||
        b->text().contains("incorrect")) {
      b->setText("incorrect");
      *valid = false;
    }
  }
}

void deposit::checked_list(QList<QLayout *> *list, QString date,
                           double *deposit_sum, int mod) {
  for (QList<QLayout *>::Iterator it = list->begin(); it != list->end(); it++) {
    QLayout *a = *it;
    QDateEdit *b = (QDateEdit *)a->itemAt(1)->widget();
    QRadioButton *c = (QRadioButton *)a->itemAt(0)->widget();
    QString d = b->date().toString();
    if (d == date) {
      if (!mod) {
        *deposit_sum += c->text().toDouble();
      } else {
        *deposit_sum -= c->text().toDouble();
      }
    }
  }
}

void deposit::add_text(QWidget *wd, QString text, int mod) {
  if (!mod) {
    QLabel *a = (QLabel *)wd;
    if (!a->text().contains("incorrect")) {
      a->setText(a->text().append(text));
    } else {
      a->setText("");
      if (!text.contains(".")) {
        a->setText(a->text().append(text));
      }
    }
  } else if (mod == 1) {
    QRadioButton *a = (QRadioButton *)wd;
    if (!a->text().contains("incorrect")) {
      a->setText(a->text().append(text));
    } else {
      a->setText("");
      if (!text.contains(".")) {
        a->setText(a->text().append(text));
      }
    }
  }
}

void deposit::all_numbers_func_ch() {
  QPushButton *obj = (QPushButton *)sender();
  QString text = obj->text();
  if (ui->term_r_button->isChecked()) {
    add_text(ui->show_term, text, 0);
  } else if (ui->percent_r_button->isChecked()) {
    add_text(ui->show_percent, text, 0);
  } else if (ui->tax_r_button->isChecked()) {
    add_text(ui->show_tax, text, 0);
  } else if (ui->deposit_amount_r_botton->isChecked()) {
    add_text(ui->show_deposit_amount, text, 0);
  } else {
    bool next = false;
    if (this->list_add.count()) {
      next = checked_list(&this->list_add, text);
    }
    if (!next && this->list_deb.count()) {
      checked_list(&this->list_deb, text);
    }
  }
}

void deposit::on_dot_clicked() {
  QPushButton *obj = (QPushButton *)sender();
  QString text = obj->text();
  if (ui->percent_r_button->isChecked() &&
      !ui->show_percent->text().contains(text) &&
      !ui->show_percent->text().isEmpty()) {
    add_text(ui->show_percent, text, 0);
  } else if (ui->tax_r_button->isChecked() &&
             !ui->show_tax->text().contains(text) &&
             !ui->show_tax->text().isEmpty()) {
    add_text(ui->show_tax, text, 0);
  } else if (ui->deposit_amount_r_botton->isChecked() &&
             !ui->show_deposit_amount->text().contains(text) &&
             !ui->show_deposit_amount->text().isEmpty()) {
    add_text(ui->show_deposit_amount, text, 0);
  } else {
    bool next = false;
    if (this->list_add.count()) {
      next = checked_list(&this->list_add, text);
    }
    if (!next && this->list_deb.count()) {
      checked_list(&this->list_deb, text);
    }
  }
}

void deposit::on_del_clicked() {
  if (ui->term_r_button->isChecked()) {
    ui->show_term->setText("");
  } else if (ui->percent_r_button->isChecked()) {
    ui->show_percent->setText("");
  } else if (ui->tax_r_button->isChecked()) {
    ui->show_tax->setText("");
  } else if (ui->deposit_amount_r_botton->isChecked()) {
    ui->show_deposit_amount->setText("");
  } else {
    bool next = false;
    if (this->list_add.count()) {
      next = checked_list(&this->list_add);
    }
    if (!next && this->list_deb.count()) {
      checked_list(&this->list_deb);
    }
  }
}

void deposit::on_periodicity_clicked() {
  if (ui->periodicity->text().contains("days")) {
    ui->periodicity->setText("month");
  } else if (ui->periodicity->text().contains("month")) {
    ui->periodicity->setText("year");
  } else {
    ui->periodicity->setText("days");
  }
}

void deposit::add_element_list(QList<QLayout *> *list, QLayout *vl) {
  QVBoxLayout *b = (QVBoxLayout *)vl;
  if (!list->count()) {
    QHBoxLayout *a = new QHBoxLayout;
    b->addLayout(a);
    a->addWidget(new QRadioButton);
    QRadioButton *d = (QRadioButton *)a->itemAt(0)->widget();
    d->setStyleSheet(ui->term_r_button->styleSheet());
    d->setMinimumSize(ui->term_r_button->minimumSize());
    a->addWidget(new QDateEdit);
    QDateEdit *i = (QDateEdit *)a->itemAt(1)->widget();
    i->setStyleSheet(ui->contribution_calendar->styleSheet());
    i->setMinimumSize(ui->contribution_calendar->minimumSize());
    list->append(a);
  } else {
    QRadioButton *c = (QRadioButton *)list->back()->itemAt(0)->widget();
    if (!c->text().isEmpty() && !c->text().endsWith(".")) {
      QHBoxLayout *a = new QHBoxLayout;
      b->addLayout(a);
      a->addWidget(new QRadioButton);
      QRadioButton *d = (QRadioButton *)a->itemAt(0)->widget();
      d->setStyleSheet(ui->term_r_button->styleSheet());
      d->setMinimumSize(ui->term_r_button->minimumSize());
      a->addWidget(new QDateEdit);
      QDateEdit *i = (QDateEdit *)a->itemAt(1)->widget();
      i->setStyleSheet(ui->contribution_calendar->styleSheet());
      i->setMinimumSize(ui->contribution_calendar->minimumSize());
      list->append(a);
    }
  }
}

void deposit::rm_element_list(QList<QLayout *> *list) {
  if (list->count()) {
    QWidget *a = list->back()->itemAt(0)->widget();
    QWidget *b = list->back()->itemAt(1)->widget();
    delete a;
    delete b;
    delete list->back();
    list->pop_back();
  }
}

bool deposit::eqils_valid() {
  bool vl = true;
  if (!text_valid(ui->show_term->text())) {
    ui->show_term->setText("incorrect");
    vl = false;
  }
  if (!text_valid(ui->show_percent->text())) {
    ui->show_percent->setText("incorrect");
    vl = false;
  }
  if (!text_valid(ui->show_tax->text())) {
    ui->show_tax->setText("incorrect");
    vl = false;
  }
  if (!text_valid(ui->show_deposit_amount->text())) {
    ui->show_deposit_amount->setText("incorrect");
    vl = false;
  }
  checked_list(&this->list_add, &vl);
  checked_list(&this->list_deb, &vl);
  return vl;
}

bool deposit::text_valid(QString text) {
  return !text.isEmpty() && !text.endsWith(".") && !text.contains("incorrect")
             ? true
             : false;
}

void deposit::on_calculate_clicked() {
  if (eqils_valid()) {
    double sum_deposit = ui->show_deposit_amount->text().toDouble();
    QDate dinamyc_date = ui->contribution_calendar->date();
    double dinamyc_percent = 0;
    double sum_percent = 0;
    for (int i = 0; i < ui->show_term->text().toInt(); i++) {
      checked_list(&this->list_add, dinamyc_date.toString(), &sum_deposit, 0);
      checked_list(&this->list_deb, dinamyc_date.toString(), &sum_deposit, 1);
      if (ui->capitalization->isChecked()) {
        dinamyc_percent += (sum_deposit / 100 / dinamyc_date.daysInYear()) *
                           ui->show_percent->text().toDouble();
        if (ui->periodicity->text().contains("month")) {
          if (dinamyc_date.day() == ui->contribution_calendar->date().day() &&
              dinamyc_date.month() >
                  ui->contribution_calendar->date().month()) {
            sum_deposit += dinamyc_percent;
            sum_percent += dinamyc_percent;
            dinamyc_percent = 0;
          }
        } else if (ui->periodicity->text().contains("year")) {
          if (dinamyc_date.day() == ui->contribution_calendar->date().day() &&
              dinamyc_date.month() ==
                  ui->contribution_calendar->date().month()) {
            sum_deposit += dinamyc_percent;
            sum_percent += dinamyc_percent;
            dinamyc_percent = 0;
          }
        }
      } else if (!ui->capitalization->isChecked() ||
                 (ui->capitalization->isChecked() &&
                  (ui->periodicity->text().contains("day")))) {
        dinamyc_percent = (sum_deposit / 100 / dinamyc_date.daysInYear()) *
                          ui->show_percent->text().toDouble();
        sum_percent += dinamyc_percent;
        dinamyc_percent = 0;
      }
      dinamyc_date = dinamyc_date.addDays(1);
    }
    ui->res_persent_show->setText(
        QString::number(round(dinamyc_percent + sum_percent)));
    ui->res_amount_show->setText(QString::number(round(sum_deposit)));
    ui->res_tax_show->setText(
        QString::number(round(((dinamyc_percent + sum_percent) / 100) *
                              ui->show_tax->text().toDouble())));
  }
}
