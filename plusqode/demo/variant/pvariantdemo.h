#ifndef PVARIANTDEMO_H
#define PVARIANTDEMO_H

#include <QtCore/QPoint>

#include "core/pdemo.h"
#include "misc/pdebug.h"

class PVariantDemo : public PDemo {

public:
    PVariantDemo();
};

Q_DECLARE_METATYPE(QString*)
Q_DECLARE_METATYPE(int*)

#endif // PVARIANTDEMO_H
