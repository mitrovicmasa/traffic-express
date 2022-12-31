#ifndef ACTIONCARD_H
#define ACTIONCARD_H

#include <banditcard.h>
#include <serializable.h>

enum class ActionType {
    MOVE,
    FLOOR_CHANGE,
    MARSHAL,
    FIRE,
    PUNCH,
    ROBBERY
};

class ActionCard : public BanditCard, public Serializable {

public:
    ActionCard();

    // Constructors
    ActionCard(ActionType action, BanditType bandit);
    Card *Copy() const override;

    // Destructor
    ~ActionCard();

    // Get methods
    ActionType action() const;

    // Set methods
    void setAction(ActionType newAction);

    // Other methods
    std::string toString() const override;
    CardType Type() const override;

    // GUI
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Serializable interface
    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

private:
    ActionType m_action;
};

#endif // ACTIONCARD_H
