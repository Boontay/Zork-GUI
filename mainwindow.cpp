#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

template <typename T>
void addItem(vector<T> v, T t)
{
    v.push_back(t);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit_2->setTextColor(QColor("red"));
    ui->textEdit_3->setTextColor(QColor("green"));

    ui->textEdit->append(QString::fromStdString(zork->printWelcome() + "\n"));
    printCharacterStats();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    goRoom("south");
}

void MainWindow::on_pushButton_2_clicked()
{
    goRoom("west");
}

void MainWindow::on_pushButton_3_clicked()
{
    goRoom("north");
}

void MainWindow::on_pushButton_4_clicked()
{
    goRoom("east");
}

void MainWindow::on_pushButton_5_clicked()
{
    goRoom("teleport");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit->append(QString::fromStdString(character.longDescription()));
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit->append(QString::fromStdString(zork->printHelp()));
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->textEdit->append(QString::fromStdString(zork->teleport() + "\n"));
}

void MainWindow::on_pushButton_9_clicked()
{
    putInInventory = true;
    vector<Item> items = zork->getCurrentRoom().viewItems();
    listItems(items, "room");
}

void MainWindow::on_pushButton_10_clicked()
{
    putInInventory = false;
    //vector<Item> items = character.itemsInCharacter;
    vector<Item> items = character.viewItems();
    listItems(items, "character");
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem*item)
{
    string description = item->text().toStdString();
    Item i = *new Item(description);
    ui->listWidget->takeItem(ui->listWidget->row(item));
    //delete item;

    if (putInInventory)
    {
        Room r = zork->getCurrentRoom();
        Item m = r.findItem(i);
        //character.itemsInCharacter.push_back(m);
        addItem(character.itemsInCharacter, m);
        character.addItem(&m);
        r.removeItem(m);
        ui->textEdit->append(QString::fromStdString(description + " has been added to your inventory.\n"));
        overencumberedTest();
    }
    else
    {
        Item m = character.findItem(i);
        Room r = zork->getCurrentRoom();
        addItem(r.itemsInRoom, m);
        character.removeItem(m);
        ui->textEdit->append(QString::fromStdString(description + " has been removed from yuor inventory.\n"));
    }
}

void MainWindow::addItemsToListWidget(vector<Item> items)
{
    ui->listWidget->clear();

    if (putInInventory)
    {
        if (!zork->getCurrentRoom().allItemsCollected())
        {
            for (unsigned int i = 0; (unsigned int)i < (unsigned int)zork->getCurrentRoom().numberOfItems(); i++)
            {
                ui->listWidget->addItem(QString::fromStdString(items[i].getShortDescription()));
            }
        }
        else {
            ui->textEdit->append(QString::fromStdString("There are no items in the room."));
        }
    }
    else
    {
        if (!character.itemsInCharacter.empty())
        {
            for (unsigned int i = 0; i < character.itemsInCharacter.size(); i++)
            {
                ui->listWidget->addItem(QString::fromStdString(items[i].getShortDescription()));
            }
        }
        else
        {
            ui->textEdit->append(QString::fromStdString("There are no items in " + character.shortDescription() + "'s inventory.\n"));
        }
    }
}

void MainWindow::endGameState(string message1, string message2)
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->listWidget->setEnabled(false);

    ui->textEdit->setText(QString::fromStdString(character.description + " has " + message1 + ". You have " + message2 + " the game.\n"));

    character.stamina = 0;
    character.health = 0;
    ui->textEdit_2->setText(QString::fromStdString(displayHealth()));
    ui->textEdit_3->setText(QString::fromStdString(displayStamina()));
}

void MainWindow::overencumberedTest()
{
    if (character.isOverencumbered(4.0))
    {
        endGameState("been overencumberd", "lost");
    }
}

void MainWindow::goRoom(string direction)
{
    if (character.health != 0 && character.stamina >= 0)
    {
        character.decrementStamina();
        printCharacterStats();

        if (direction == "teleport")
        {
            ui->textEdit->append(QString::fromStdString(zork->teleport() + "\n"));
        }
        else
        {
            ui->textEdit->append(QString::fromStdString(zork->go(direction) + "\n"));

            if (zork->getCurrentRoom().description == "j")
            {
                endGameState("entered the winning Room", "won");
            }
        }
    }
    else
    {
        endGameState("ran out of health", "lost");
    }
}

void MainWindow::listItems(vector<Item> items, QString description)
{
    if (!items.empty())
    {
        addItemsToListWidget(items);
    }
    else
    {
        ui->textEdit->append("No " + description + " items could be found.\n");
    }
}

string MainWindow::displayStamina()
{
    string output = "Stamina:\n";

    for (int i = 0; i < character.stamina; i++)
    {
        output += "[] ";
    }

    return output;
}

string MainWindow::displayHealth()
{
    string output = "Health:\n";

    for (int i = 0; i < character.getHealth(); i++)
    {
        output += "+ ";
    }

    return output;
}

void MainWindow::printCharacterStats()
{
    if (!(character.health > 0))
    {
        endGameState("run out of health", "lost");
    }
    else
    {
        ui->textEdit_2->setText(QString::fromStdString(displayHealth()));
        ui->textEdit_3->setText(QString::fromStdString(displayStamina()));
    }
}
