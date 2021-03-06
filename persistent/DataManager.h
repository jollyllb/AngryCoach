#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QHash>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QSharedPointer>
#include "CustomQHashSerializer.h"
#include "DayLogCache.h"

class DayLog;
class Food;
class FoodRecipe;
class AppData;
class FoodMap;
class RecipeMap;

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = 0);

    FoodMap* getFood();
    RecipeMap* getRecipes();
    void addFood(Food* food);
    void removeFood(const QString& foodId);
    void addRecipe(FoodRecipe* recipe);
    void removeRecipe(const QString& recipeId);

    AppData* getData();
    DayLog* getDayLog(const QDate& date);
    void addFoodToLog(const QDate& date, const QString& foodId, float foodAmount);
    void removeFoodFromLog(const QDate& date, int index);
    void addRecipeToLog(const QDate& date, const QString& recipeId, float amount);
    void removeRecipeFromLog(const QDate& date, int index);
    void save();

    static QDir getDataDir();

private: // members
    AppData* _data = nullptr;
    QFile* _dataFile = nullptr;
    QHash<QDate, QSharedPointer<DayLogCache>> _dayLogCache;

private: // methods
    void load();
    void initNewSave();
    QSharedPointer<DayLogCache> getDayLogCache(const QDate& date);


public slots:
    void saveDayLog(const QDate& date);
};

#endif // DATAMANAGER_H
