#ifndef SRC_CALC_DEPOSIT_H_
#define SRC_CALC_DEPOSIT_H_

#include <QWidget>

namespace Ui {
class deposit;
}

class deposit : public QWidget {
  Q_OBJECT

public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

private:
  Ui::deposit *ui;
  bool capital = false;
  QList<QLayout *> list_add;
  QList<QLayout *> list_deb;

private slots:
  void all_numbers_func_ch();
  void on_dot_clicked();
  void on_del_clicked();
  void on_periodicity_clicked();
  void on_calculate_clicked();
  bool eqils_valid();
  bool checked_list(QList<QLayout *> *list, QString text);
  bool checked_list(QList<QLayout *> *list);
  void checked_list(QList<QLayout *> *list, bool *valid);
  void checked_list(QList<QLayout *> *list, QString date, double *deposit_sum,
                    int mod);
  void add_text(QWidget *wd, QString text, int mod);
  void add_element_list(QList<QLayout *> *list, QLayout *vl);
  void rm_element_list(QList<QLayout *> *list);
  bool text_valid(QString text);
};

#endif // SRC_CALC_DEPOSIT_H_
