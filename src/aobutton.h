#pragma once

#include "aoapplication.h"

#include <QDebug>
#include <QMovie>
#include <QPushButton>

class AOButton : public QPushButton
{
  Q_OBJECT

public:
  AOButton(QWidget *parent, AOApplication *p_ao_app);
  ~AOButton();

  AOApplication *ao_app;
  QMovie *movie;

  void set_image(QString p_image, QString p_misc = "");
};
