#ifndef GAMERECORD
#define GAMERECORD

#include <QString>
#include <QMap>

enum PropType {
    //Move properties
    BLACK_MOVE, //B
    KO, //KO
    MOVE_NUMBER, //MN
    WHITE_MOVE, //W

    //Setup properties
    ADD_BLACK, //AB
    ADD_ERASE, //AE
    ADD_WHITE, //AW
    PLAYER_TURN, //PL

    //Node annotation properties
    COMMENT, //C
    EVEN_POSITION, //DM
    GOOD_FOR_BLACK, //GB
    GOOD_FOR_WHITE, //GW
    HOTSPOT, //HO
    NODE_NAME, //N
    UNCLEAR_POS, //UC
    NODE_VALUE, //V

    //Move annotation properties
    BAD_MOVE, //BM
    DOUBTFUL_MOVE, //DO
    INTERESTING_MOVE, //IT
    TESUJI_MOVE, //TE

    //Markup properties
    ARROW_MARK, //AR
    CIRCLE_MARK, //CR
    DIM_POINT, //DD
    TEXT_MARK, //LB
    LINE_MARK, //LN
    X_MARK, //MA
    SELECTED_POINT, //SL
    SQUARE_MARK, //SQ
    TRIANGLE_MARK, //TR

    //Root properties
    APPLICATION, //AP
    CHARSET, //CA
    FILE_FORMAT, //FF
    GAME_TYPE, //GM
    VARIATIONS_SHOW, //ST
    SIZE, //SZ

    //Game info properties
    ANNOTATION_PERSON_NAME, //AN
    BLACK_RANK, //BR
    BLACK_TEAM, //BT
    COPYRIGHT, //CP
    PLAYED_DATE, //DT
    EVENT_NAME, //EV
    GAME_NAME, //GN
    EXTRA_INFO, //GC
    OPENING_INFO, //ON
    OVERTIME_METHOD, //OT
    BLACK_PLAYER, //PB
    PLACE, //PC
    WHITE_PLAYER, //PW
    RESULT, //RE
    ROUND, //RO
    RULES, //RU
    SOURCE, //SO
    TIME_LIMIT, //TM
    USER_NAME, //US
    WHITE_RANK, //WR
    WHITE_TEAM, //WT

    //Timing properties
    BLACK_TIME_LEFT, //BL
    BLACK_MOVE_LEFT, //OB
    WHITE_MOVE_LEFT, //OW
    WHITE_TIME_LEFT, //WL

    //Miscellaneous properties
    FIGURE_PROP, //FG
    PRINTING_METHOD, //PM
    VIEW_PART, //VW

    //GO specific properties
    HANDICAP, //HA
    KOMI, //KM
    BLACK_TERRITORY, //TB
    WHITE_TERRITORY, //TW

    UNKNOWN
};

class RecordNode {
public:
    int pos_x;
    int pos_y;
    PropType moveType;
    QMap<PropType, QList<QString> *> extraProps;
    QList<RecordNode *> childrens;
    RecordNode *parent;

    RecordNode(RecordNode *node = NULL);
    void setParent(RecordNode *parent);
    QString toString();
    QString nodeToStr(RecordNode *node);
    int childCount();
    RecordNode *getParent();
    int row();
    QString getCoordinate();
};

#endif // GAMERECORD

