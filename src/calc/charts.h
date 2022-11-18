#ifndef SRC_CALC_CHARTS_H_
#define SRC_CALC_CHARTS_H_

#include <QVector>
#include <QWidget>
#ifdef __cplusplus
extern "C" {
#endif
#include "c_calc.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class charts;
}

class charts : public QWidget {
  Q_OBJECT
public:
  explicit charts(QWidget *parent = nullptr);
  ~charts();

private:
  Ui::charts *ui;
  QString expresssion;
  double xMin = 0;
  double xMax = 0;
  double interval = 0;
  bool min_v = false;
  bool max_v = false;
  bool interval_v = false;
  QVector<double> x, y;

public slots:
  void expfc(const QString &text);
private slots:
  void all_numbers_func_ch();
  void on_dot_clicked();
  void on_del_clicked();
  void on_build_clicked();
  void min_valid(QString a);
  void max_valid(QString a);
  void interval_valid(QString a);
  void on_minus_clicked();
  void clean_build();
};

#endif // SRC_CALC_CHARTS_H_
