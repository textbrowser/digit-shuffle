#include <QApplication>
#include <QtDebug>

#include "digit-shuffle.h"

int main(int argc, char *argv[])
{
  QApplication application(argc, argv);
  digit_shuffle ds;

  ds.show();
  return application.exec();
}
