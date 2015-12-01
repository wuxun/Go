#ifndef GAMERECORD
#define GAMERECORD

#include <QString>

class metaData {
    QString recordType; //GM[1]
    QString application; //AP
    QString charset; //CA
};

class GameInfo {
public:
    QString blackName; //PB
    QString whiteName; //PW
    QString blackRank; //BR
    QString whiteRank; //WR
    QString blackTeam; //BT
    QString whiteTeam; //WT
    QString result; //RE
    float komi; //KO
    int size; //SZ
    int handicap; //HA
    int time; //TM; Regular playing time for each side in seconds
    QString date; //DT
    QString event; //EV
    QString round; //RO
    QString place; //PC
    QString rules; //RU
    QString gameName; //GN
    QString opening; //ON
    QString gameComment; //GC
    QString Source; //SO
    QString user; //US
    QString annotation; //AN
    QString copyRight; //CP
};

class RecordNode {
    QList<RecordNode *> childrens;
};

class GameRecord {
private:
    GameInfo info;
    QList<RecordNode *> nodes;
};

#endif // GAMERECORD

