#ifndef QMLDATAPROVIDER_H
#define QMLDATAPROVIDER_H

#include <QDate>
#include <QObject>
#include <QList>
#include <QVariant>
class DataManager;
class Food;
class FoodRecipe;

class QmlDataProvider : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QVariantList food READ getFood NOTIFY foodChanged)
    Q_PROPERTY(QVariantList recipes READ getRecipes NOTIFY recipesChanged)
    QmlDataProvider(QObject* parent = 0);

    Q_PROPERTY(QDate selectedDate READ getSelectedDate WRITE setSelectedDate NOTIFY selectedDateChanged)
    Q_PROPERTY(QVariantMap userProfile READ getUserProfileModel NOTIFY userProfileChanged)

    const QDate& getSelectedDate() const;
    void setSelectedDate(const QDate& date);

    // food
    Q_INVOKABLE void addFood(const QVariantMap& data);
    Q_INVOKABLE void editFood(const QString& foodId, const QVariantMap& data);
    Q_INVOKABLE void removeFood(const QString& foodId);
    QVariantList getFood();
    Q_INVOKABLE QObject* getFoodById(const QString& foodId);

    // recipe
    Q_INVOKABLE void addRecipe(const QVariantMap& data);
    Q_INVOKABLE void editRecipe(const QString& recipeId, const QVariantMap& data);
    Q_INVOKABLE void removeRecipe(const QString& recipeId);
    QVariantList getRecipes();
    Q_INVOKABLE QObject* getRecipeById(const QString& recipeId);

    // day log

    // returns object with keys:
    // Food -> array of FoodAmount
    // Recipes -> array of FoodAmount
    Q_INVOKABLE QVariantMap getDayLog(const QDate& date);
    Q_INVOKABLE void addFoodToLog(const QDate& date, const QString& foodId, float foodAmount);
    Q_INVOKABLE void addRecipeToLog(const QDate& date, const QString& recipeId, float amount);
    Q_INVOKABLE void removeFoodFromLog(const QDate& date, int index);
    Q_INVOKABLE void removeRecipeFromLog(const QDate& date, int index);
    Q_INVOKABLE void editFoodAmount(const QDate& date, int index, float amount);
    Q_INVOKABLE void editRecipeAmount(const QDate& date, int index, float amount);
    Q_INVOKABLE QVariantMap getFoodValuesForForm(const QString& foodId);
    Q_INVOKABLE QVariantMap getUserProfileModel();
    Q_INVOKABLE void updateUserProfile(const QVariantMap& data);
    Q_INVOKABLE QVariantMap getRecipeValuesForForm(const QString& recipeId);

signals:
    void foodChanged();
    void recipesChanged();
    void dayLogChanged(const QDate& date);
    void selectedDateChanged();
    void userProfileChanged();

private: // methods
    Food* findFood(const QString& foodId);
    FoodRecipe* findRecipe(const QString& recipeId);
    float getFloat(const QVariant& variant) const;
    void mapDataToFood(Food* food, const QVariantMap& data);
    void mapDataToRecipe(FoodRecipe* recipe, const QVariantMap& data);
    QString getStringFromFloat(float value);

private: // members
    DataManager* _dataManager;
    QDate _selectedDate;
};

#endif // QMLDATAPROVIDER_H
