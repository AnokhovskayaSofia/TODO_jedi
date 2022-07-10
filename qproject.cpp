#include "qproject.h"

void qProject::setValue(QString text)
{
    this->value = text;
}

void qProject::setParent(qProject *parent)
{
    this->m_parentItem = parent;
}
