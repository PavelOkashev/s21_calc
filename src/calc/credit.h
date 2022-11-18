#ifndef SRC_CALC_CREDIT_H_
#define SRC_CALC_CREDIT_H_

#include <QWidget>
#include <cmath>

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT
public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

private:
  Ui::credit *ui;
  bool type = false;

private slots:
  void all_numbers_func_ch();
  void on_dot_clicked();
  void on_del_clicked();
  void on_type_clicked();
  bool eqils_valid(QWidget *a);
  void on_calculate_clicked();
};

#endif // SRC_CALC_CREDIT_H_
