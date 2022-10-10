#ifndef ISOTOPE_H
#define ISOTOPE_H
#include <QString>

class isotope
{
public:
    isotope(QString name, int modality);
    ~isotope();

private:
    QString m_qsIsotopeName;
    int m_iModality;

};

#endif // ISOTOPE_H
