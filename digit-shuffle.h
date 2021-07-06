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

  void compute(const QVector<int> &cols,
	       const QVector<int> &rows,
	       const QVector<int> &solutions)
  {
    QVector<int> results;
    const int a = solutions.at(0);
    const int b = solutions.at(1);
    const int c = solutions.at(2);
    const int d = solutions.at(3);
    const int e = solutions.at(4);
    const int f = solutions.at(5);

    for(int x1 = 1; x1 <= 9; x1++)
      for(int x2 = 1; x2 <= 9; x2++)
	for(int x3 = 1; x3 <= 9; x3++)
	  for(int x4 = 1; x4 <= 9; x4++)
	    for(int x5 = 1; x5 <= 9; x5++)
	      for(int x6 = 1; x6 <= 9; x6++)
		for(int x7 = 1; x7 <= 9; x7++)
		  for(int x8 = 1; x8 <= 9; x8++)
		    for(int x9 = 1; x9 <= 9; x9++)
		      {
			if(m_future.isCanceled())
			  goto done_label;

			// Columns!

			int c1 = x1;
			int c2 = x2;
			int c3 = x3;

			switch(cols.at(0))
			  {
			  case 0:
			    c1 += x4;
			    break;
			  case 1:
			    c1 -= x4;
			    break;
			  case 2:
			    c1 /= x4;
			    break;
			  default:
			    c1 *= x4;
			    break;
			  }

			switch(cols.at(1))
			  {
			  case 0:
			    c1 += x7;
			    break;
			  case 1:
			    c1 -= x7;
			    break;
			  case 2:
			    c1 /= x7;
			    break;
			  default:
			    c1 *= x7;
			    break;
			  }

			switch(cols.at(2))
			  {
			  case 0:
			    c2 += x5;
			    break;
			  case 1:
			    c2 -= x5;
			    break;
			  case 2:
			    c2 /= x5;
			    break;
			  default:
			    c2 *= x5;
			    break;
			  }

			switch(cols.at(3))
			  {
			  case 0:
			    c2 += x8;
			    break;
			  case 1:
			    c2 -= x8;
			    break;
			  case 2:
			    c2 /= x8;
			    break;
			  default:
			    c2 *= x8;
			    break;
			  }

			switch(cols.at(4))
			  {
			  case 0:
			    c3 += x6;
			    break;
			  case 1:
			    c3 -= x6;
			    break;
			  case 2:
			    c3 /= x6;
			    break;
			  default:
			    c3 *= x6;
			    break;
			  }

			switch(cols.at(5))
			  {
			  case 0:
			    c3 += x9;
			    break;
			  case 1:
			    c3 -= x9;
			    break;
			  case 2:
			    c3 /= x9;
			    break;
			  default:
			    c3 *= x9;
			    break;
			  }

			// Rows!

			int r1 = x1;
			int r2 = x4;
			int r3 = x7;

			switch(rows.at(0))
			  {
			  case 0:
			    r1 += x2;
			    break;
			  case 1:
			    r1 -= x2;
			    break;
			  case 2:
			    r1 /= x2;
			    break;
			  default:
			    r1 *= x2;
			    break;
			  }

			switch(rows.at(1))
			  {
			  case 0:
			    r1 += x3;
			    break;
			  case 1:
			    r1 -= x3;
			    break;
			  case 2:
			    r1 /= x3;
			    break;
			  default:
			    r1 *= x3;
			    break;
			  }

			switch(rows.at(2))
			  {
			  case 0:
			    r2 += x5;
			    break;
			  case 1:
			    r2 -= x5;
			    break;
			  case 2:
			    r2 /= x5;
			    break;
			  default:
			    r2 *= x5;
			    break;
			  }

			switch(rows.at(3))
			  {
			  case 0:
			    r2 += x6;
			    break;
			  case 1:
			    r2 -= x6;
			    break;
			  case 2:
			    r2 /= x6;
			    break;
			  default:
			    r2 *= x6;
			    break;
			  }

			switch(rows.at(4))
			  {
			  case 0:
			    r3 += x8;
			    break;
			  case 1:
			    r3 -= x8;
			    break;
			  case 2:
			    r3 /= x8;
			    break;
			  default:
			    r3 *= x8;
			    break;
			  }

			switch(rows.at(5))
			  {
			  case 0:
			    r3 += x9;
			    break;
			  case 1:
			    r3 -= x9;
			    break;
			  case 2:
			    r3 /= x9;
			    break;
			  default:
			    r3 *= x9;
			    break;
			  }

			if(a == r1 &&
			   b == r2 &&
			   c == r3 &&
			   d == c1 &&
			   e == c2 &&
			   f == c3)
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
