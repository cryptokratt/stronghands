#ifndef OPTIONSMODEL_H
#define OPTIONSMODEL_H

#include <QAbstractListModel>

/** Interface from QT to configuration data structure for bitcoin client.
   To QT, the options are presented as a list with the different options
   laid out vertically.
   This can be changed to a tree once the settings become sufficiently
   complex.
 */
class OptionsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit OptionsModel(QObject *parent = 0);

    enum OptionID {
        StartAtStartup, // bool
        MinimizeToTray, // bool
        MapPortUPnP, // bool
        MinimizeOnClose, // bool
        ConnectSOCKS4, // bool
        ProxyIP, // QString
        ProxyPort, // QString
        Fee, // qint64
        DisplayUnit, // BitcoinUnits::Unit
        DisplayAddresses, // bool
        DetachDatabases, // bool
        CoinControlFeatures, // bool
        OptionIDRowCount,
    };

    void Init();

    /* Migrate settings from wallet.dat after app initialization */
    bool Upgrade(); /* returns true if settings upgraded */

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    /* Explicit getters */
    qint64 getTransactionFee();
    bool getMinimizeToTray();
    bool getMinimizeOnClose();
    int getDisplayUnit();
    bool getDisplayAddresses();
    bool getCoinControlFeatures();

private:
    int nDisplayUnit;
    bool bDisplayAddresses;
    bool fMinimizeToTray;
    bool fMinimizeOnClose;
    bool fCoinControlFeatures;

    const QString& getOverriddenByCommandLine() { return strOverriddenByCommandLine; }
    QString strOverriddenByCommandLine;

    /// Add option to list of GUI options overridden through command line/config file
    void addOverriddenOption(const std::string &option);

signals:
    void displayUnitChanged(int unit);
    void transactionFeeChanged(qint64);
    void coinControlFeaturesChanged(bool);
};

#endif // OPTIONSMODEL_H
