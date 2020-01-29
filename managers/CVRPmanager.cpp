﻿#include "CVRPmanager.h"
#include "ui_CVRPmanager.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include <ctime>

#include "utils/fileutils.h"

#include <cg3/data_structures/arrays/arrays.h>
#include <cg3/utilities/timer.h>

#include <algorithms/cvrp.h>
#include <algorithms/cvrpar.h>


//Constants for scene reset
//Do not change the following lines
const double SCENERADIUS = 1e+5;
const cg3::Pointd SCENECENTER(0,0,0);



//----------------------------------------------------------------------------------------------
//                         You have to write your code in the area below.
//----------------------------------------------------------------------------------------------



/* ----- Constructors/Destructors ----- */

/**
 * @brief Default constructor of the manager
 */
CVRPmanager::CVRPmanager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CVRPmanager),
    mainWindow(static_cast<cg3::viewer::MainWindow&>(*parent))
{
    //UI setup
    ui->setupUi(this);

    //Setting options for the canvas
    mainWindow.disableRotation();
    mainWindow.setSelectLeftButton();

    //Add the drawable object to the mainWindow.
    //The mainWindow will take care of rendering the bounding box

    //This updates the canvas (call it whenever you change or
    //add some drawable object)
    mainWindow.updateGlCanvas();

    fitScene();
}


/**
 * @brief Destructor of the manager
 */
CVRPmanager::~CVRPmanager() {

    eraseDrawnRoutes();

    delete ui; //Delete interface
}



/* ----- Private main methods ----- */

/**
 * @brief Launch the selected Cvrp algorithm
 */
void CVRPmanager::computeCvrpAlgorithm(const Topology& topology) {

    int selected = this->ui->selectVersion->currentIndex();

    switch(selected)
    {
    case(0):
        cWseq(topology,this->singleRoutes);
        break;
    case(1):
        cWseqInversion(topology,this->singleRoutes);
        break;
    case(2):
        cWseqSqueamish(topology,this->singleRoutes);
        break;
    case(3):
        cWseqSqueamishInversion(topology,this->singleRoutes);
        break;
    case(4):
        cWseqMerge(topology,this->singleRoutes);
        break;
    case(5):
        cWpar(topology,this->singleRoutes);
        break;
    case(6):
        cWparInversion(topology,this->singleRoutes);
        break;
    case(7):
        cWparRandomized(topology,this->singleRoutes);
        break;
    /*case(8):

        Adjacency_list network(4);
        network.addArc(0,1,10,0,10);
        network.addArc(0,2,6,0,6);
        network.addArc(1,2,1,0,1);
        network.addArc(1,3,8,0,8);
        network.addArc(2,3,10,0,10);

        Adjacency_list residual = convertToResidual(network);
        int i = 0;
        i++;*/
    }
}


/**
 * @brief Clear data of the routes
 */
void CVRPmanager::clearRoutes() {

    eraseDrawnRoutes();
    this->singleRoutes.clear();

}



/**
 * @brief Draw the routes in the canvas
 */
void CVRPmanager::drawRoutes() {

    std::string routeName;

    for(size_t i = 0;i < this->singleRoutes.size();i++){

        routeName = "Route ";
        routeName += std::to_string(i+1);

        mainWindow.pushObj(&this->singleRoutes[i],routeName);
    }

    //Canvas update
    mainWindow.updateGlCanvas();
}

/**
 * @brief Erase drawn routes from the canvas
 */
void CVRPmanager::eraseDrawnRoutes() {

    for(size_t i = 0;i < this->singleRoutes.size();i++){

        mainWindow.deleteObj(&this->singleRoutes[i]);
    }

    //Canvas update
    mainWindow.updateGlCanvas();
}


/* ----- Private utility methods ----- */

/**
 * @brief Launch the algorithm of this manager and measure
 * its time efficiency.
 */
void CVRPmanager::launchAlgorithmAndMeasureTime(const Topology& topology) {
    //Output message

    //Timer for evaluating the efficiency of the algorithm
    cg3::Timer t("Computing cvrp");

    //Launch cvrp selected algorithm on the topology
    computeCvrpAlgorithm(topology);

    //Timer stop and visualization (both on console and UI)
    t.stopAndPrint();
    ui->timeLabel->setNum(t.delay());

    time = t.delay();
    std::cout << std::endl;
}

/**
 * @brief Change camera of the canvas to fit the scene
 */
void CVRPmanager::fitScene() {
    mainWindow.fitScene(SCENECENTER, SCENERADIUS);
}




/* ----- UI slots for loading points ----- */

/**
 * @brief Load topology from file
 *
 * Load the topology from a file.
 */
void CVRPmanager::on_loadFilePushButton_clicked() {
    //File selector
    /*QString filename = QFileDialog::getOpenFileName(nullptr,
                       "Open points",
                       ".",
                       "*.txt");

    if (!filename.isEmpty()) {

        //Delete from the canvas the routes
        eraseDrawnRoutes();

        //Clear current data
        clearRoutes();



        std::string name = filename.toStdString();

        //Load the topology from the file

        Topology topology = FileUtils::getTopologyFromFile(filename.toStdString());


        int selected = this->ui->selectVersion->currentIndex();

        switch(selected)
        {
        case(0):
            name += "_cWseq_test";
            break;
        case(1):
            name += "_cWseqInversion_test";
            break;
        case(2):
            name += "_cWseqSqueamish_test";
            break;
        case(3):
            name += "_cWseqSqueamishInversion_test";
            break;
        case(4):
            name += "_cWseqMerge_test";
            break;
        case(5):
            name += "_cWpar_test";
            break;
        case(6):
            name += "_cWparInversion_test";
            break;
        case(7):
            name += "_cWparRandomized_test";
            break;
        }

        //Launch the algorithm and measure
        //its efficiency with a timer

        launchAlgorithmAndMeasureTime(topology);

        writeOnExistingFile(this->singleRoutes,topology.getNode_num(),name,time);

        //Draw the routes
        drawRoutes();

    }
    */

    Adjacency_list network(12);


    //third topology
    network.addArc(0,0,1,4);
    network.addArc(0,0,4,3);
    network.addArc(0,0,7,7);
    network.addArc(0,0,2,6);
    network.addArc(0,1,3,6);
    network.addArc(0,1,6,4);
    network.addArc(0,1,10,12);
    network.addArc(0,1,4,2);
    network.addArc(0,2,4,1);
    network.addArc(0,2,8,2);
    network.addArc(0,2,5,8);
    network.addArc(0,3,11,10);
    network.addArc(0,4,7,4);
    network.addArc(0,5,8,6);
    network.addArc(0,6,9,4);
    network.addArc(0,7,9,3);
    network.addArc(0,7,11,10);
    network.addArc(0,7,8,5);
    network.addArc(0,8,11,10);
    network.addArc(0,9,11,10);
    network.addArc(0,10,11,10);



    //second topology
    /*network.addArc(0,0,1,5);
    network.addArc(0,0,2,5);
    network.addArc(0,0,4,5);
    network.addArc(0,1,3,5);
    network.addArc(0,3,0,5);
    network.addArc(0,4,9,5);
    network.addArc(0,3,5,5);
    network.addArc(0,5,6,5);
    network.addArc(0,5,10,5);
    network.addArc(0,6,7,5);
    network.addArc(0,7,11,5);
    network.addArc(0,9,12,5);
    network.addArc(0,12,8,5);
    network.addArc(0,8,9,5);
    network.addArc(0,8,13,5);
    network.addArc(0,2,4,5);
    network.addArc(0,6,3,5);
    network.addArc(0,10,8,5);
    network.addArc(0,11,13,5);*/


    //first topology
    /*network.addArc(0,0,1,2);
    network.addArc(0,0,2,4);
    network.addArc(0,1,3,1);
    network.addArc(0,1,2,3);
    network.addArc(0,2,3,5);*/

    //Adjacency_list residual = convertToResidual(network);
    /*std::vector<pFPnode> nodes;
    nodes.resize(14);
    //computeDistanceLabels(network, nodes);

    preProcess(network,nodes);
    int i = 0;
    i++;*/

    preFlowPush(network);
}

/**
 * @brief Clear routes button event handler.
 *
 * It allows us to clear our routes.
 */
void CVRPmanager::on_clearRoutesPushButton_clicked() {

    //Clear current data
    clearRoutes();

    //Delete from the canvas the routes
    eraseDrawnRoutes();

    //Clear timer data

    ui->timeLabel->setText("");
}

/* ----- UI slots for utilities ----- */

/**
 * @brief Reset scene event handler.
 *
 * It allows us to reset the camera of the canvas to
 * show/center the scene
 */
void CVRPmanager::on_resetScenePushButton_clicked() {
    fitScene();
}
