#include "MainMenu.h"

MainMenu::MainMenu() // in the constructor, we create EVERYTHING in the main menu
{

    /*-------------------------------------------------------------
    First, We Set the Foundation for the MainMenu
    -------------------------------------------------------------*/
    active = true;
    // We define the menu manager pointer and the menu pointers

    Manager = new MenuManager; // creates a new Menu manager
    Menu opMenu(ofVec2f(0,0)); // creating the options menu
    Menu normalMenu(ofVec2f(0,0)); // creating the normal menu
    Menu credMenu(ofVec2f(0,0)); // creating credits menu
    Menu quitMenu(ofVec2f(0,0));//creating quit y/n? menu

    //Here we add ALL of the Textures
    Manager->addTexture("XNormal", "XButtonNormal.png"); // adding textures in the format Manager->addTexture("Name you will refer to the texture with", "File_Name")
    Manager->addTexture("XHovered", "XButtonHovered.png");
    Manager->addTexture("XPressed", "XButtonPressed.png");

    Manager->addTexture("OrangeBackground", "OrangeBackground.png");

    Manager->addTexture("BlueButton", "BlueButton.pngDefaultQuitButton");
    Manager->addTexture("ClickedBlueButton", "ClickedBlueButton.png");
    Manager->addTexture("PressedBlueButton", "PressedBlueButton.png");
    Manager->addTexture("HoveredBlueButton", "HoveredBlueButton.png");
    Manager->addTexture("PressedClickedBlueButton", "PressedClickedBlueButton.png");

    Manager->addTexture("DolphinBackground", "DolphinBackground.png");

    Manager->addTexture("StartGameButtonNormal", "PlayButtonNormal.png");
    Manager->addTexture("StartGameButtonPressed", "PlayButtonPressed.png");
    Manager->addTexture("StartGameButtonHovered", "PlayButtonHovered.png");

    Manager->addTexture("CreditsBackground", "Credits.png");

    Manager->addTexture("StandardNormal", "StandardNormal.png");
    Manager->addTexture("StandardPressed", "StandardPressed.png");
    Manager->addTexture("StandardHovered", "StandardHovered.png");

    Manager->addTexture("YesExitNormal", "YesButton.png");
    Manager->addTexture("YesExitPressed", "YesButton.png");
    Manager->addTexture("YesExitHovered", "YesButton.png");

    Manager->addTexture("NoExitNormal", "NormalNoButton.png");
    Manager->addTexture("NoExitPressed", "NormalNoButton.png");
    Manager->addTexture("NoExitHovered", "NormalNoButton.png");

    Manager->addTexture("ReallyQuitBackground", "ReallyQuitBackground.png");

    Manager->addTexture("OptionsNormal", "OptionsButtonNormal.png");
    Manager->addTexture("OptionsHovered", "OptionsButtonHovered.png");
    Manager->addTexture("OptionsPressed", "OptionsButtonPressed.png");

    Manager->addTexture("CreditsNormal", "CreditsButtonNormal.png");
    Manager->addTexture("CreditsHovered", "CreditsButtonHovered.png");
    Manager->addTexture("CreditsPressed", "CreditsButtonPressed.png");

    Manager->addTexture("QuitNormal", "QuitButtonNormal.png");
    Manager->addTexture("QuitHovered", "QuitButtonHovered.png");
    Manager->addTexture("QuitPressed", "QuitButtonPressed.png");



    //Here we add ALL of the fonts
    Manager->addFont("NormalFont", "MySimpleFont.ttf", 16); // adding fonts
    Manager->addFont("Baqacents", "Baqacents-Semibold.ttf", 16);
    Manager->addFont("Fancy", "Champagne-and-Limousines.ttf", 16);
    Manager->addFont("Obelisk", "Obelisk-MMXV.ttf", 16);



    /*-------------------------------------------------------------
    Now, We Begin Making Buttons
    -------------------------------------------------------------*/



    // Please use the following format for consistency and legibility:
    //Start:
    MenuEntity *brightnessSlider;
    brightnessSlider = new Slider(
                            ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/4),
                            Manager->getTexturePointer("BlueButton"),
                            Manager->getTexturePointer("XPressed"),
                            100,
                            0,
                            50,
                            Manager->getFontPointer("NormalFont"),
                            "Brightness"
                                );


    MenuEntity *exitButton; // create the exit button
    exitButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()-100, 100),                                   // position
                            Manager->getTexturePointer("XNormal"),    // Normal Texture
                            Manager->getTexturePointer("XHovered"),    // Hovered Texture
                            Manager->getTexturePointer("XPressed"),    // Pressed texture
                            Manager->getTexturePointer("XPressed"),    // Clicked Texture
                            Manager->getTexturePointer("XPressed"),    // Clicked and Hovered Texture (highly optional; here, I just repeated  the clicked texture)
                            Manager->getTexturePointer("XPressed")     // Clicked and Pressed Texture
                                  );
    //End.
    //For adding text, see line 79-92 where we create the options button



    MenuEntity *orangeBG; // Orange Background
    orangeBG = new MenuBackground(
                            ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/2), // in the middle of the window
                            Manager->getTexturePointer("OrangeBackground")
                                  );
    MenuEntity *reallyQuitBG;//quitMenu background
    reallyQuitBG = new MenuBackground(
                            ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/4),
                            Manager->getTexturePointer("ReallyQuitBackground")
                                    );


    // example for adding text
    MenuEntity *optionsButton; // options button
    optionsButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, 2*ofGetWindowHeight()/5),
                            Manager->getTexturePointer("OptionsNormal"),           // adding textures, we have done this before...
                            Manager->getTexturePointer("OptionsHovered"),
                            Manager->getTexturePointer("OptionsPressed"),
                            Manager->getTexturePointer("OptionsHovered"),
                            Manager->getTexturePointer("OptionsHovered"),
                            Manager->getTexturePointer("OptionsHovered"), // adding last texture
                            Manager->getFontPointer("NormalFont"),                  // Here we go: This is adding the font...
                            ""                                               //don't need any text, its in the texture
                                    );



    MenuEntity *creditsButton; // Credits Button
    creditsButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, 3*ofGetWindowHeight()/5),
                            Manager->getTexturePointer("CreditsNormal"),
                            Manager->getTexturePointer("CreditsHovered"),
                            Manager->getTexturePointer("CreditsPressed"),
                            Manager->getTexturePointer("CreditsPressed"),
                            Manager->getTexturePointer("CreditsPressed"),
                            Manager->getTexturePointer("CreditsPressed")
                                    );


    MenuEntity *quitGameButton; // Quit Game Button
    quitGameButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, 4*ofGetWindowHeight()/5),
                            Manager->getTexturePointer("QuitNormal"),
                            Manager->getTexturePointer("QuitHovered"),
                            Manager->getTexturePointer("QuitPressed"),
                            Manager->getTexturePointer("QuitPressed"),
                            Manager->getTexturePointer("QuitPressed"),
                            Manager->getTexturePointer("QuitPressed")
                                    );




    MenuEntity *SGButton; // Start Game Button
    SGButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/5),
                            Manager->getTexturePointer("StartGameButtonNormal"),
                            Manager->getTexturePointer("StartGameButtonHovered"),
                            Manager->getTexturePointer("StartGameButtonPressed"),
                            Manager->getTexturePointer("StartGameButtonPressed"),
                            Manager->getTexturePointer("StartGameButtonPressed"),
                            Manager->getTexturePointer("StartGameButtonPressed")
                                    );




    MenuEntity *cancelButton; // cancel Button
    cancelButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, 4*ofGetWindowHeight()/5),
                            Manager->getTexturePointer("QuitNormal"),
                            Manager->getTexturePointer("QuitHovered"),
                            Manager->getTexturePointer("QuitPressed"),
                            Manager->getTexturePointer("QuitPressed"),
                            Manager->getTexturePointer("QuitPressed"),
                            Manager->getTexturePointer("QuitPressed")
                                    );




    MenuEntity *dolphinBG; // options menu background
    dolphinBG = new MenuBackground(
                            ofVec2f(ofGetWindowWidth()/2,ofGetWindowHeight()/2),
                            Manager->getTexturePointer("DolphinBackground")
                                  );

    MenuEntity *creditsBG; // options menu background
    creditsBG = new MenuBackground(
                            ofVec2f(ofGetWindowWidth()/2,ofGetWindowHeight()/2),
                            Manager->getTexturePointer("CreditsBackground")
                                  );

    MenuEntity *yesExitButton; //exit game button
    yesExitButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/4, ofGetWindowHeight()*2/3),
                            Manager->getTexturePointer("YesExitNormal"),
                            Manager->getTexturePointer("YesExitHovered"),
                            Manager->getTexturePointer("YesExitPressed"),
                            Manager->getTexturePointer("YesExitPressed"),
                            Manager->getTexturePointer("YesExitPressed"),
                            Manager->getTexturePointer("YesExitPressed")
                                    );

    MenuEntity *noExitButton; //return to main menu button
    noExitButton = new HoverButton(
                            ofVec2f(ofGetWindowWidth()*3/4, ofGetWindowHeight()*2/3),
                            Manager->getTexturePointer("NoExitNormal"),
                            Manager->getTexturePointer("NoExitHovered"),
                            Manager->getTexturePointer("NoExitPressed"),
                            Manager->getTexturePointer("NoExitPressed"),
                            Manager->getTexturePointer("NoExitPressed"),
                            Manager->getTexturePointer("NoExitPressed")
                                    );

    /*------------------------------------------------------------------------------
    Done Making Buttons.
    Now we add the buttons to menus and the menus to Menu manager.
    ----------------------------------------------------------------------------------*/


    opMenu.addEntity(*dolphinBG, "DolphinBackground"); // adding Entities to menus...
    opMenu.addEntity(*exitButton, "ExitButton");
    opMenu.addEntity(*brightnessSlider, "setBrightness");

    normalMenu.addEntity(*orangeBG, "NormalBackground");
    normalMenu.addEntity(*SGButton, "StartGameButton");
    normalMenu.addEntity(*optionsButton, "OptionsButton");
    normalMenu.addEntity(*creditsButton, "CreditsButton");
    normalMenu.addEntity(*quitGameButton, "QuitGameButton");
    credMenu.addEntity(*creditsBG, "CreditsBackground");
    credMenu.addEntity(*cancelButton, "CancelButton");
    quitMenu.addEntity(*reallyQuitBG, "QuitBackground");
    quitMenu.addEntity(*yesExitButton, "YesExitButton");
    quitMenu.addEntity(*noExitButton, "NoExitButton");




    // now we add menus to Managers
    Manager->addMenu(normalMenu, "NormalMenu");
    Manager->addMenu(opMenu, "OptionsMenu");
    Manager->addMenu(credMenu, "CreditsMenu");
    Manager->addMenu(quitMenu, "QuitGameMenu");



    // now we define pointers to menus in the menu entities. These pointers are private elements of MainMenu
    defaultMenu = Manager->getMenuPointerByName("NormalMenu");  // definition of pointer
    defaultMenu->setActive();
                                  // set active or inactive
    optionsMenu = Manager->getMenuPointerByName("OptionsMenu");
    optionsMenu->setInactive();

    creditsMenu = Manager->getMenuPointerByName("CreditsMenu");
    creditsMenu->setInactive();

    quitGameMenu = Manager->getMenuPointerByName("QuitGameMenu");
    quitGameMenu->setInactive();



    //Lastly, we define pointers to buttons. This allows these MenuEntities to have characteristics of children of MenuEntity, like HoverButton
    Exit = optionsMenu->getPointerToChildByName<HoverButton>("ExitButton");
    OptionsBut = defaultMenu->getPointerToChildByName<HoverButton>("OptionsButton");
    StartGameButton = defaultMenu->getPointerToChildByName<HoverButton>("StartGameButton");
    CreditsBut = defaultMenu->getPointerToChildByName<HoverButton>("CreditsButton");
    CancelBut = creditsMenu->getPointerToChildByName<HoverButton>("CancelButton");
    QuitGameBut = defaultMenu->getPointerToChildByName<HoverButton>("QuitGameButton");
    YesQuitBut = quitGameMenu->getPointerToChildByName<HoverButton>("YesExitButton");
    NoQuitBut = quitGameMenu->getPointerToChildByName<HoverButton>("NoExitButton");
    BrightnessSlider = optionsMenu->getPointerToChildByName<Slider>("setBrightness");



}


void MainMenu::draw() // in the draw function, all we do is call the manager's draw function
{
    if (active == true)
    {
        Manager->draw();
    }
}




bool MainMenu::update(ofVec2f& mousePos, bool& clicked, bool& pressed) // In Update, we have all of the functionality, like clicking and swapping between menus
{
    if (active == true)
    {
         // this (if) -- (else if) statement is a good example of swapping between menus:
         //Start:
         // This if statement says that if you click the x button in the options menu, it goes back to the default menu
         if(Exit->getEventDataInt() > 2) // "Exit->getEventDataInt() > 2" essentially means that if the exit button (inside the options menu) is clicked, it passes the if test
         {                               //   ( >2 means it's clicked. 0 = nothing, 1 = hovered, 2 = pressed, 3 = clicked, 4 = hovered and clicked, 5 = pressed and clicked)
             Exit->setClicked(false);    // once the button is clicked, we immediately unclick it manually
             OptionsBut->setClicked(false); // we unclick the options button, which is in the default Menu
             optionsMenu->setInactive();    // we set the options menu to inactive (we pressed the x button)
             defaultMenu->setActive();      // we re-set the default menu to active
         }
         // This else if statement is more common than the previous if statement
         else if (defaultMenu->isActive() == true and optionsMenu->isActive() == false and OptionsBut->getEventDataInt() > 2) // translation: if you are in the default menu,
         {                                                                                                                    // and you hit the options button, the following happens:
             optionsMenu->setActive(); // the options menu pops up
             defaultMenu->setInactive();// the default menu is turned inactive
         }
         //End.


         // this if deals with the start game button -- NOT FINISHED
         if (StartGameButton->getEventDataInt() > 2)
         {
             StartGameButton->setClicked(false);
             defaultMenu->setInactive();
             active = false;

             return true;
         }

        // the following two are grouped, hopefullyStartGameButtonBut->setPosition(ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/5));
         if (CancelBut->getEventDataInt() >2) // deals with the cancel button in the credits menu
         {

             CancelBut->setClicked(false);
             CreditsBut->setClicked(false);
             creditsMenu->setInactive();
             defaultMenu->setActive();
         }

         else if (defaultMenu->isActive() == true and creditsMenu->isActive() == false and CreditsBut->getEventDataInt() > 2)
         {
             creditsMenu->setActive();
             defaultMenu->setInactive();
         }

         if (QuitGameBut->getEventDataInt() >2) // deals with the quit game button
         {
             quitGameMenu->setActive();
             QuitGameBut->setClicked(false);
             defaultMenu->setInactive();
         }

         if(quitGameMenu->isActive() == true)
         {
             if (YesQuitBut->getEventDataInt() > 2)
             {
                 quitGameMenu->setInactive();
                 YesQuitBut->setClicked(false);
                 active = false;
                 std::exit(EXIT_SUCCESS);
             }
             else if (NoQuitBut->getEventDataInt() > 2)
             {
                 quitGameMenu->setInactive();
                 NoQuitBut->setClicked(false);
                 defaultMenu->setActive();
             }
         }

         //std::cout << BrightnessSlider->getEventDataInt() << endl;//slider troubleshooting



        Exit->setPosition(ofVec2f(ofGetWindowWidth()-100, 100));
        OptionsBut->setPosition(ofVec2f(ofGetWindowWidth()/2, 2*ofGetWindowHeight()/5));
        CreditsBut->setPosition(ofVec2f(ofGetWindowWidth()/2, 3*ofGetWindowHeight()/5));
        StartGameButton->setPosition(ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/5));
        CancelBut->setPosition(ofVec2f(ofGetWindowWidth()/2, 4*ofGetWindowHeight()/5));
        QuitGameBut->setPosition(ofVec2f(ofGetWindowWidth()/2, 4*ofGetWindowHeight()/5));


        Manager->update(mousePos, clicked, pressed); // and finally, and most importantly, we update the manager



        return false;

    }

}

void MainMenu::switchActive()
{
    active = !active;
}

bool MainMenu::getActive()
{
    return active;
}
