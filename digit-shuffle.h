// Alexis Megas 2021.

#ifndef _digit_shuffle_
#define _digit_shuffle_

#include <QFuture>
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

  static int op(const int a, const int b, const int o)
  {
    switch(o)
      {
      case 0:
	return a + b;
      case 1:
	return a - b;
      case 2:
	if(b != 0)
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

  void compute(const QVector<int> &cols,
	       const QVector<int> &rows,
	       const QVector<int> &solutions)
  {
    QVector<int> results;
    const int a = solutions.at(0);
    const int b = solutions.at(1);
    const int c = solutions.at(2);
    const int c3 = cols.at(2);
    const int c4 = cols.at(3);
    const int c5 = cols.at(4);
    const int c6 = cols.at(5);
    const int d = solutions.at(3);
    const int e = solutions.at(4);
    const int f = solutions.at(5);
    const int r1 = rows.at(0);
    const int r2 = rows.at(1);
    const int r3 = rows.at(2);
    const int r4 = rows.at(3);
    const int r5 = rows.at(4);
    const int r6 = rows.at(5);
    int x1 = 1;
    int x2 = 1;
    int x3 = 1;
    int x4 = 1;
    int x7 = 1;

    for(int x5 = 1; x5 <= 9; x5++)
      for(int x6 = 1; x6 <= 9; x6++)
	for(int x8 = 1; x8 <= 9; x8++)
	  for(int x9 = 1; x9 <= 9; x9++)
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

	      if(x1 <= 0 || x1 > 9 ||
		 x2 <= 0 || x2 > 9 ||
		 x3 <= 0 || x3 > 9 ||
		 x4 <= 0 || x4 > 9 ||
		 x7 <= 0 || x7 > 9)
		continue;

	      // Columns!

	      int v1 = x1;
	      int v2 = x2;
	      int v3 = x3;

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

	      int v4 = x1;
	      int v5 = x4;
	      int v6 = x7;

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

	      if(a == v4 &&
		 b == v5 &&
		 c == v6 &&
		 d == v1 &&
		 e == v2 &&
		 f == v3)
		{
		  QList<int> list;
		  QSet<int> set;

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
		      results << x1
			      << x2
			      << x3
			      << x4
			      << x5
			      << x6
			      << x7
			      << x8
			      << x9;
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
    statusBar()->showMessage("");
  }

  void slot_quit(void)
  {
    QApplication::instance()->quit();
  }

  void slot_reset(void)
  {
    foreach(auto widget, findChildren<QComboBox *> ())
      if(widget)
	widget->setCurrentIndex(0);

    foreach(auto widget, findChildren<QSpinBox *> ())
      if(widget)
	widget->setValue(0);
  }

  void slot_solve(void)
  {
    statusBar()->showMessage(tr("Canceling current operation..."));
    m_future.cancel();
    m_future.waitForFinished();
    statusBar()->showMessage(tr("Solving..."));

    QVector<int> cols;
    QVector<int> rows;
    QVector<int> solutions;

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
    m_future = QtConcurrent::run
      (this, &digit_shuffle::compute, cols, rows, solutions);
  }

 signals:
  void computed(const QVector<int> &results);
};

#endif
