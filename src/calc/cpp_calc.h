#ifndef SRC_CALC_CPP_CALC_H_
#define SRC_CALC_CPP_CALC_H_

#include "charts.h"
#include "credit.h"
#include "deposit.h"
#include <QMainWindow>
#include <qcustomplot.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "c_calc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class cpp_calc;
}
QT_END_NAMESPACE

class cpp_calc : public QMainWindow {
  Q_OBJECT

public:
  explicit cpp_calc(QWidget *parent = nullptr);
  ~cpp_calc();

private:
  bool eq = false;
  bool is_dot = false;
  int b_count = 0;
  Ui::cpp_calc *ui;
  charts *chart;
  credit *credit_calc;
  deposit *deposit_calc;

signals:
  void ewx(const QString &text);

private slots:
  void all_numbers_func();
  void binari_func();
  void on_dot_clicked();
  void minus_and_plus_func();
  void br_func();
  void unari_func();
  bool num_valid(QString a);
  void on_del_clicked();
  void on_num_x_clicked();
  void on_eq_clicked();

  void on_credit_triggered();
  void on_deposit_triggered();
};
#endif //  SRC_CALC_CPP_CALC_H_
