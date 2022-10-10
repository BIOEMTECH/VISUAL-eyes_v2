////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file Search.cpp
///
///	@brief database search platform and opening selected experiment to post processing dialog-editor.
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
///////////////////////////////////////////////////////////////////////////////////////////////////


#include "headers/Search.h"
#include "ui_Search.h"

cSqlTableQueryModel::cSqlTableQueryModel(QObject *parent) :QSqlTableModel(parent){}

void cSqlTableQueryModel::setQueryAndStore(const QSqlQuery &query)
{
    setQuery(query);
    //  mQueryStr = query;
}

Qt::ItemFlags cSqlTableQueryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    return flags;
}

bool cSqlTableQueryModel::setData(const QModelIndex &index)
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    return true;
}

QVariant cSqlTableQueryModel::data(const QModelIndex& index, int role) const { return QSqlQueryModel::data(index, role);}

Search::Search( ReadInputInfo* readInput, QWidget *parent) :
    QDialog(parent), ui(new Ui::Search), m_pReadInputInfo( 0 )
{
    m_pReadInputInfo = readInput;
    ui->setupUi(this);
    ui->qd_startDate->setDate(QDate::currentDate());
    ui->qd_endDate->setDate(QDate::currentDate());
    ui->check_animal->setChecked(false);
    ui->check_Inpath->setChecked(false);
    ui->check_marking->setChecked(false);
    ui->check_name->setChecked(false);
    ui->check_nuclide->setChecked(false);
    ui->check_op->setChecked(false);
    postProc=nullptr;
}

Search::~Search()
{
    if(postProc!=nullptr)
        postProc->deleteLater();
    delete ui;
}

void Search::Init()
{
    QSortFilterProxyModel *m = new QSortFilterProxyModel(this);	  ////// make table sortable
    m->setDynamicSortFilter(true);
    m->setSourceModel(&mSqlTableQueryModel);
    ui->TV_studies->setModel(&mSqlTableQueryModel);
    ui->TV_studies->setSortingEnabled(true);

    ui->TV_studies->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TV_studies->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->TV_studies->show();

    QSqlQuery query,q,q2;
    QString nuclides = "SELECT * FROM radionuclide ";
    query.exec(nuclides);
    if(query.first()) {
        do {
            QString name = query.value("nuclide_name").toString();
            int nid = query.value("nuclide_id").toInt();
            ui->cB_nuclide->addItem(name,nid);
        }while(query.next());
    }

    ui->cB_inj_path->clear();
    q.exec("SELECT * FROM InjectionPath ");
    if(q.first())
    {
        do {
            QString p_name = q.value("name").toString();
            int id = q.value("path_id").toInt();
            ui->cB_inj_path->addItem(p_name,id);
        }while(q.next());
    }

    QString op = "SELECT * FROM operator";
    q2.exec(op);
    if(q2.first()){
        do{
            QString name = q2.value("name").toString();
            int nid = q2.value("operator_id").toInt();
            ui->cB_op->addItem(name,nid);
        }while(q2.next());
    }

    connect(ui->pb_dateSearch, SIGNAL( pressed() ),this, SLOT( dateSearch() ) );
     connect(ui->TV_studies, SIGNAL( doubleClicked(QModelIndex) ), this, SLOT(on_double_click_table_item(QModelIndex)));
    connect(ui->pb_comboSearch, SIGNAL( clicked() ),this, SLOT( comboSearch() ) );
}

void Search::ResiseTable(int rows)
{
    for (int i = 0; i<rows; i++)
        ui->TV_studies->verticalHeader()->resizeSection(i, 29);
}

void Search::dateSearch()
{
    QString from_date;
    QString to_date;

    from_date =  ui->qd_startDate->date().toString("yyyy/MM/dd");
    to_date = ui->qd_endDate->date().toString("yyyy/MM/dd");

    QString d = "SELECT Study.study_id, Study.date, Study.name, Study.animal_name, Study.breed, Study.species, Study.age, Study.weight, Study.gender, Study.r_pharma ,Study.volume ,Study.activity, Study.injection_date, InjectionPath.name as Path , Study.exp_duration as ExpirimentDuration, Study.frame as FrameDuration ,Study.start_time as AquisitionStartTime, Study.fin_time as AquisitionFinishTime , device.name as Device, ";
            d += "modality.mod_name, Study.operator_name as Operator, radionuclide.nuclide_name as Radionuclide ,Study.project, Study.injected_activity, Study.comments, Study.marking, Study.fileDirectory ";
            d += "FROM Study ";
            d += "INNER JOIN InjectionPath ON Study.path_id = InjectionPath.path_id ";
            d +="INNER JOIN device ON Study.deviceid = device.deviceid ";
            d +="INNER JOIN modality ON Study.id_modality = modality.id_modality ";
            d +="INNER JOIN radionuclide ON Study.nuclide_id = radionuclide.nuclide_id ";
            d +="WHERE (Study.date >= '"+from_date+"' AND Study.date <= '"+to_date+"')";

#ifdef QT_DEBUG
    qDebug() << d;
#endif

    TableQuery(d);
}

void Search::comboSearch()
{
    QString sName,animalID,marking,op;
    QString n_id,path_id;

    sName = ui->LE_name->text();
    animalID = ui->LE_animal->text();
    op = ui->cB_op->currentText();
    marking = ui->LE_marking->text();
    n_id = ui->cB_nuclide->currentData().toString();
    path_id = ui->cB_inj_path->currentData().toString();


    QString d = "SELECT Study.study_id, Study.date, Study.name, Study.animal_name, Study.breed, Study.species, Study.age, Study.weight, Study.gender, Study.r_pharma ,Study.volume ,Study.activity, Study.injection_date, InjectionPath.name as Path , Study.exp_duration as ExpirimentDuration, Study.frame as FrameDuration ,Study.start_time as AquisitionStartTime, Study.fin_time as AquisitionFinishTime , device.name as Device, ";
    d += "modality.mod_name, Study.operator_name as Operator, radionuclide.nuclide_name as Radionuclide ,Study.project, Study.injected_activity, Study.comments, Study.marking, Study.fileDirectory ";
    d += "FROM Study ";
    d += "INNER JOIN InjectionPath ON Study.path_id = InjectionPath.path_id ";
    d +="INNER JOIN device ON Study.deviceid = device.deviceid ";
    d +="INNER JOIN modality ON Study.id_modality = modality.id_modality ";
    d +="INNER JOIN radionuclide ON Study.nuclide_id = radionuclide.nuclide_id ";
    d +="WHERE ";


    if ( ui->check_name->isChecked() )
        d+=  " Study.name = '" + sName + "' AND";
    else if ( ui->check_marking->isChecked() )
        d+= " Study.marking = '" + marking + "' AND";
    else if ( ui->check_Inpath->isChecked() )
        d+= " Study.path_id  = '" + path_id + "' AND";
    else if ( ui->check_animal->isChecked() )
        d+= " Study.animal_name = '" + animalID + "' AND";
    else if ( ui->check_nuclide->isChecked() )
        d+= " Study.nuclide_id = '" + n_id + "' AND";
    else if ( ui->check_op->isChecked() )
        d+= " Study.operator_name = '" + op + "' AND";


    if ( boost::ends_with(d, "AND") )
        d.chop( 3 );

#ifdef QT_DEBUG
    qDebug() << d;
#endif

    TableQuery( d );
}

void Search::TableQuery(QString q)
{
    QSqlQuery query;
    query.exec(q);

    mSqlTableQueryModel.setObjectName("Study");
    mSqlTableQueryModel.setEditStrategy(QSqlTableModel::OnFieldChange);
    mSqlTableQueryModel.setQueryAndStore(query);
    mSqlTableQueryModel.setHeaderData(0, Qt::Horizontal, QObject::tr("ID"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(1, Qt::Horizontal, QObject::tr("Date"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(2, Qt::Horizontal, QObject::tr("Study \nname"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(3, Qt::Horizontal, QObject::tr("Animal \nname"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(4, Qt::Horizontal, QObject::tr("Animal \nbreed"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(5, Qt::Horizontal, QObject::tr("Animal \nSpecies"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(6, Qt::Horizontal, QObject::tr("Animal \nage"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(7, Qt::Horizontal, QObject::tr("Animal \nweight"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(8, Qt::Horizontal, QObject::tr("Animal \ngender"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(9, Qt::Horizontal, QObject::tr("Radiopharmaceutical"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(10, Qt::Horizontal, QObject::tr("Volume"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(11, Qt::Horizontal, QObject::tr("Activity"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(12, Qt::Horizontal, QObject::tr("Injection \ndate"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(13, Qt::Horizontal, QObject::tr("Injection \npath"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(14, Qt::Horizontal, QObject::tr("Experiment \nduration"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(15, Qt::Horizontal, QObject::tr("Frame per"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(16, Qt::Horizontal, QObject::tr("Aquisition \nstart time"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(17, Qt::Horizontal, QObject::tr("Aquisition \nfinish time"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(18, Qt::Horizontal, QObject::tr("Device"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(19, Qt::Horizontal, QObject::tr("Modality"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(20, Qt::Horizontal, QObject::tr("Operator"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(21, Qt::Horizontal, QObject::tr("Radionuclide"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(22, Qt::Horizontal, QObject::tr("Project"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(23, Qt::Horizontal, QObject::tr("Injected \nactivity"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(24, Qt::Horizontal, QObject::tr("Comments"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(25, Qt::Horizontal, QObject::tr("Marking"), Qt::DisplayRole);
    mSqlTableQueryModel.setHeaderData(26, Qt::Horizontal, QObject::tr("FileDirectory"), Qt::DisplayRole);

    for ( int col = 0; col < 27; col++ )
        ui->TV_studies->resizeColumnToContents( col ); //  setColumnWidth(, 200);


    ResiseTable( mSqlTableQueryModel.rowCount( QModelIndex() ) );
#ifdef QT_DEBUG
    QString msg = mSqlTableQueryModel.lastError().text();
    qDebug() << msg;
#endif

    ui->TV_studies->show();
}

int Search::getRowID(QStringList &lst, int column)
{
    QItemSelectionModel *selections = ui->TV_studies->selectionModel();
    QModelIndex index;

    int rowSize = mSqlTableQueryModel.rowCount(QModelIndex());
    for (int i = 0; i<rowSize; i++) {
        index = mSqlTableQueryModel.index(i, column, QModelIndex());
        if (selections->isSelected(index))
            lst.append(mSqlTableQueryModel.data(index, Qt::DisplayRole).toString());
    }
    return lst.count();
}

void Search::on_double_click_table_item(QModelIndex)
{
    postProc = new PostProcessing( m_pReadInputInfo, this);

    QStringList strList;
    int count = getRowID(strList,0);

    for (int i = 0; i<count; i++){
        QString str = strList.at(i);
        postProc->show();
        postProc->Init(str);
    }
}
