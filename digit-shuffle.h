// Alexis Megas, 2021.

#ifndef _digit_shuffle_
#define _digit_shuffle_

#include <QFuture>
#ifdef Q_OS_ANDROID
#if (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
#include <QJniObject>
#endif
#endif
#include <QtConcurrent>
#include <QtDebug>

#include "ui_digit-shuffle.h"

class digit_shuffle: public QMainWindow
{
  Q_OBJECT

 public:
  digit_shuffle(void)
  {
    m_ui.setupUi(this);
    connect(m_ui.action_quit,
	    SIGNAL(triggered(void)),
	    this,
	    SLOT(slot_quit(void)));
    connect(m_ui.reset,
	    SIGNAL(clicked(void)),
	    this,
	    SLOT(slot_reset(void)));
    connect(m_ui.solve,
	    SIGNAL(clicked(void)),
	    this,
	    SLOT(slot_solve(void)));
    connect(this,
	    SIGNAL(computed(const QVector<int> &)),
	    this,
	    SLOT(slot_computed(const QVector<int> &)));
  }

  ~digit_shuffle()
  {
    m_future.cancel();
    m_future.waitForFinished();
  }

 private:
  QFuture<void> m_future;
  Ui_digit_shuffle m_ui;

  static double op(const double a, const double b, const int o)
  {
    switch(o)
      {
      case 0:
	return a + b;
      case 1:
	return a - b;
      case 2:
	if(b < 0.0 || b > 0.0)
	  return a / b;
	else
	  return a;
      default:
	return a * b;
      }
  }

  static int op_inverse(const int o)
  {
    switch(o)
      {
      case 0: // +
	return 1; // -
      case 1: // -
	return 0; // +
      case 2: // /
	return 3; // *
      default: // *
	return 2; // /
      }
  }

  void compute(const QVector<double> &solutions,
	       const QVector<int> &cols,
	       const QVector<int> &rows)
  {
    QVector<int> results;
    auto const a = solutions.at(0);
    auto const b = solutions.at(1);
    auto const c = solutions.at(2);
    auto const c3 = cols.at(2);
    auto const c4 = cols.at(3);
    auto const c5 = cols.at(4);
    auto const c6 = cols.at(5);
    auto const d = solutions.at(3);
    auto const e = solutions.at(4);
    auto const f = solutions.at(5);
    auto const r1 = rows.at(0);
    auto const r2 = rows.at(1);
    auto const r3 = rows.at(2);
    auto const r4 = rows.at(3);
    auto const r5 = rows.at(4);
    auto const r6 = rows.at(5);
    double x1 = 1.0;
    double x2 = 1.0;
    double x3 = 1.0;
    double x4 = 1.0;
    double x7 = 1.0;

    for(double x5 = 1.0; x5 <= 9.0; x5 += 1.0)
      for(double x6 = 1.0; x6 <= 9.0; x6 += 1.0)
	for(double x8 = 1.0; x8 <= 9.0; x8 += 1.0)
	  for(double x9 = 1.0; x9 <= 9.0; x9 += 1.0)
	    {
	      if(m_future.isCanceled())
		goto done_label;

	      x2 = op(e, x8, op_inverse(c4));
	      x2 = op(x2, x5, op_inverse(c3));
	      x3 = op(f, x9, op_inverse(c6));
	      x3 = op(x3, x6, op_inverse(c5));
	      x1 = op(a, x3, op_inverse(r2));
	      x1 = op(x1, x2, op_inverse(r1));
	      x4 = op(b, x6, op_inverse(r4));
	      x4 = op(x4, x5, op_inverse(r3));
	      x7 = op(c, x9, op_inverse(r6));
	      x7 = op(x7, x8, op_inverse(r5));

	      if(qFuzzyCompare(x1, 0.0) || x1 < 0.0 || x1 > 9.0 ||
		 qFuzzyCompare(x2, 0.0) || x2 < 0.0 || x2 > 9.0 ||
		 qFuzzyCompare(x3, 0.0) || x3 < 0.0 || x3 > 9.0 ||
		 qFuzzyCompare(x4, 0.0) || x4 < 0.0 || x4 > 9.0 ||
		 qFuzzyCompare(x7, 0.0) || x7 < 0.0 || x7 > 9.0)
		continue;

	      // Columns!

	      auto v1 = x1;
	      auto v2 = x2;
	      auto v3 = x3;

	      switch(cols.at(0))
		{
		case 0:
		  v1 += x4;
		  break;
		case 1:
		  v1 -= x4;
		  break;
		case 2:
		  v1 /= x4;
		  break;
		default:
		  v1 *= x4;
		  break;
		}

	      switch(cols.at(1))
		{
		case 0:
		  v1 += x7;
		  break;
		case 1:
		  v1 -= x7;
		  break;
		case 2:
		  v1 /= x7;
		  break;
		default:
		  v1 *= x7;
		  break;
		}

	      switch(cols.at(2))
		{
		case 0:
		  v2 += x5;
		  break;
		case 1:
		  v2 -= x5;
		  break;
		case 2:
		  v2 /= x5;
		  break;
		default:
		  v2 *= x5;
		  break;
		}

	      switch(cols.at(3))
		{
		case 0:
		  v2 += x8;
		  break;
		case 1:
		  v2 -= x8;
		  break;
		case 2:
		  v2 /= x8;
		  break;
		default:
		 v2 *= x8;
		  break;
		}

	      switch(cols.at(4))
		{
		case 0:
		  v3 += x6;
		  break;
		case 1:
		  v3 -= x6;
		  break;
		case 2:
		  v3 /= x6;
		  break;
		default:
		  v3 *= x6;
		  break;
		}

	      switch(cols.at(5))
		{
		case 0:
		  v3 += x9;
		  break;
		case 1:
		  v3 -= x9;
		  break;
		case 2:
		  v3 /= x9;
		  break;
		default:
		  v3 *= x9;
		  break;
		}

	      // Rows!

	      auto v4 = x1;
	      auto v5 = x4;
	      auto v6 = x7;

	      switch(rows.at(0))
		{
		case 0:
		  v4 += x2;
		  break;
		case 1:
		  v4 -= x2;
		  break;
		case 2:
		  v4 /= x2;
		  break;
		default:
		  v4 *= x2;
		  break;
		}

	      switch(rows.at(1))
		{
		case 0:
		  v4 += x3;
		  break;
		case 1:
		  v4 -= x3;
		  break;
		case 2:
		  v4 /= x3;
		  break;
		default:
		  v4 *= x3;
		  break;
		}

	      switch(rows.at(2))
		{
		case 0:
		  v5 += x5;
		  break;
		case 1:
		  v5 -= x5;
		  break;
		case 2:
		  v5 /= x5;
		  break;
		default:
		  v5 *= x5;
		  break;
		}

	      switch(rows.at(3))
		{
		case 0:
		  v5 += x6;
		  break;
		case 1:
		  v5 -= x6;
		  break;
		case 2:
		  v5 /= x6;
		  break;
		default:
		  v5 *= x6;
		  break;
		}

	      switch(rows.at(4))
		{
		case 0:
		  v6 += x8;
		  break;
		case 1:
		  v6 -= x8;
		  break;
		case 2:
		  v6 /= x8;
		  break;
		default:
		  v6 *= x8;
		  break;
		}

	      switch(rows.at(5))
		{
		case 0:
		  v6 += x9;
		  break;
		case 1:
		  v6 -= x9;
		  break;
		case 2:
		  v6 /= x9;
		  break;
		default:
		  v6 *= x9;
		  break;
		}

	      if(!(a < v4 || a > v4) &&
		 !(b < v5 || b > v5) &&
		 !(c < v6 || c > v6) &&
		 !(d < v1 || d > v1) &&
		 !(e < v2 || e > v2) &&
		 !(f < v3 || f > v3))
		{
		  QList<double> list;
		  QSet<double> set;

		  list << x1
		       << x2
		       << x3
		       << x4
		       << x5
		       << x6
		       << x7
		       << x8
		       << x9;
		  set << x1
		      << x2
		      << x3
		      << x4
		      << x5
		      << x6
		      << x7
		      << x8
		      << x9;

		  if(list.size() == set.size())
		    {
		      results << static_cast<int> (x1)
			      << static_cast<int> (x2)
			      << static_cast<int> (x3)
			      << static_cast<int> (x4)
			      << static_cast<int> (x5)
			      << static_cast<int> (x6)
			      << static_cast<int> (x7)
			      << static_cast<int> (x8)
			      << static_cast<int> (x9);
		      goto done_label;
		    }
		}
	    }

  done_label:

    if(!m_future.isCanceled())
      emit computed(results);
  }

 private slots:
  void slot_computed(const QVector<int> &results)
  {
    m_ui.x1->setValue(results.value(0));
    m_ui.x2->setValue(results.value(1));
    m_ui.x3->setValue(results.value(2));
    m_ui.x4->setValue(results.value(3));
    m_ui.x5->setValue(results.value(4));
    m_ui.x6->setValue(results.value(5));
    m_ui.x7->setValue(results.value(6));
    m_ui.x8->setValue(results.value(7));
    m_ui.x9->setValue(results.value(8));

    if(results.isEmpty())
      statusBar()->showMessage(tr("A solution does not exist."), 5000);
    else
      statusBar()->showMessage("");
  }

  void slot_quit(void)
  {
    QApplication::instance()->quit();
#ifdef Q_OS_ANDROID
#if (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
    auto activity = QJniObject
      (QNativeInterface::QAndroidApplication::context());

    activity.callMethod<void> ("finishAndRemoveTask");
#endif
#endif
  }

  void slot_reset(void)
  {
    foreach(auto widget, findChildren<QComboBox *> ())
      if(widget)
	widget->setCurrentIndex(0);

    foreach(auto widget, findChildren<QDoubleSpinBox *> ())
      if(widget)
	widget->setValue(0);
  }

  void slot_solve(void)
  {
    statusBar()->showMessage(tr("Canceling current operation..."));
    m_future.cancel();
    m_future.waitForFinished();
    statusBar()->showMessage(tr("Solving..."));

    QVector<double> solutions;
    QVector<int> cols;
    QVector<int> rows;

    cols << m_ui.c1->currentIndex();
    cols << m_ui.c2->currentIndex();
    cols << m_ui.c4->currentIndex();
    cols << m_ui.c5->currentIndex();
    cols << m_ui.c7->currentIndex();
    cols << m_ui.c8->currentIndex();
    rows << m_ui.r1->currentIndex();
    rows << m_ui.r2->currentIndex();
    rows << m_ui.r4->currentIndex();
    rows << m_ui.r5->currentIndex();
    rows << m_ui.r7->currentIndex();
    rows << m_ui.r8->currentIndex();
    solutions << m_ui.a->value();
    solutions << m_ui.b->value();
    solutions << m_ui.c->value();
    solutions << m_ui.d->value();
    solutions << m_ui.e->value();
    solutions << m_ui.f->value();
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    m_future = QtConcurrent::run
      (this, &digit_shuffle::compute, solutions, cols, rows);
#else
    m_future = QtConcurrent::run
      (&digit_shuffle::compute, this, solutions, cols, rows);
#endif
  }

 signals:
  void computed(const QVector<int> &results);
};

#endif
