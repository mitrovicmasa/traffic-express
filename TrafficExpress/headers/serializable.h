#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <qvariant.h>

class Serializable {
 public:
  Serializable();

  virtual ~Serializable() = default;
  // Metod toVariant() sluzi za opisivanje na koji nacin se vrsi serijalizacija.
  virtual QVariant toVariant() const = 0;
  // Metod toVariant() sluzi za opisivanje na koji nacin se vrsi
  // deserijalizacija.
  virtual void fromVariant(const QVariant& variant) = 0;
};

#endif  // SERIALIZABLE_H
