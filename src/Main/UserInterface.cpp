#include "UserInterface.hpp"

module::module(Rectangle rect, int textSize, std::string name, Texture2D texture)
{
	this->rect = rect;
	this->textSize = textSize;
	this->name = name;
	this->content = "";
	this->texture = texture;
	this->textPos.y = this->rect.y + this->rect.height / 2 - textSize / 2;
	this->textPos.x = this->rect.x + this->textSize / 2;
}

module::~module()
{

}

bool module::IsPressed(Vector2 mousePos)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsHovered(mousePos))
		return true;
	return false;
}

bool module::IsHovered(Vector2 mousePos)
{
	if (CheckCollisionPointRec(mousePos, rect))
		return true;
	return false;
}

void module::update()
{
	if (funcSet)
		func();
}

void module::draw()
{
	Rectangle srcRec = { 0, 0, (float)texture.width, (float)texture.height };
	DrawTexturePro(texture, srcRec, this->rect, {0,0}, 0.0f, WHITE);
	if (IsHovered(*mp))
	{
		DrawRectangleRec(rect, { 100,100,100,150 });
	}
	DrawTextEx(f, content.c_str(), textPos, (float)textSize, 1, WHITE);
}

void module::AsignFunc(std::function<void()> func)
{
	this->func = func;
	funcSet = true;
}

ValueModule::ValueModule(Rectangle rect, int textSize, std::string name, Texture2D texture, int* val, int* val2) : module(rect, textSize, name, texture)
{
	this->val = val;
	this->val2 = val2;
}

ValueModule::~ValueModule()
{

}

void ValueModule::update()
{
	module::update();
	if (val)
		content = name + ": " + std::to_string(*val);
	if (val2)
		content += " " + std::to_string(*val2);
}

Slider::Slider(Rectangle rect, int textSize, std::string name, Texture2D texture)
: module(rect, textSize, name, texture)
{
	imin = 0;
	imax = 0;
	fmin = 0.0f;
	fmax = 0.0f;
	ival = nullptr;
	fval = nullptr;
	sliderRect = {rect.x, rect.y + rect.height, rect.width, rect.height};
	sliderPos.y = sliderRect.y + sliderRect.height / 2;
	sliderSize = sliderRect.height / 2;
}

Slider::~Slider()
{

}

void Slider::SetPointer(int* ival, float* fval)
{
	this->ival = ival;
	this->fval = fval;
}

void Slider::SetBounds(int imin, int imax, float fmin, float fmax)
{
	this->imin = imin;
	this->imax = imax;
	this->fmin = fmin;
	this->fmax = fmax;
	if (ival)
	{
		sliderPos.x = rect.width * (*ival - imin) / (imax - imin) + rect.x;
		if (*ival > imax)
			*ival = imax;
		else if (*ival < imin)
			*ival = imin;
		content = name + ": " + std::to_string(*ival);
	}
	else if (fval)
	{
		sliderPos.x = rect.width * (*fval - fmin) / (fmax - fmin) + rect.x;
		if (*fval > fmax)
			*fval = fmax;
		else if (*fval < fmin)
			*fval = fmin;
		content = name + ": " + std::to_string(*fval);
	}
}

bool Slider::IsPressed(Vector2 mousePos)
{
	if (module::IsPressed(mousePos) || (CheckCollisionPointRec(mousePos, sliderRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || isSlid)
	{
		isSlid = true;
		if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			isSlid = false;
			if (funcSet)
				func();
		}
		else if (CheckCollisionPointRec(mousePos, sliderRect))
		{
			return true;
		}
		return isSlid;
	}
	return false;
}

void Slider::update()
{
	if (ival)
	{
		if (*ival > imax)
			*ival = imax;
		else if (*ival < imin)
			*ival = imin;
		content = name + ": " + std::to_string(*ival);
	}
	else if (fval)
	{
		if (*fval > fmax)
			*fval = fmax;
		else if (*fval < fmin)
			*fval = fmin;
		content = name + ": " + std::to_string(*fval);
	}
	sliderPos.x = mp->x;
	if (sliderPos.x > rect.x + rect.width)
		sliderPos.x = rect.x + rect.width;
	else if (sliderPos.x < rect.x)
		sliderPos.x = rect.x;
	if (ival)
		*ival = (int)((sliderPos.x - rect.x) / rect.width * (imax - imin) + imin);
	else if (fval)
		*fval = (sliderPos.x - rect.x) / rect.width * (fmax - fmin) + fmin;
}

void Slider::draw()
{
	module::draw();
	Rectangle srcRec = { 0, 0, (float)texture.width, (float)texture.height };
	DrawTexturePro(texture, srcRec, sliderRect, {0,0}, 0.0f, WHITE);
	srcRec = { 0,0, (float)sliderTexture.width, (float)sliderTexture.height };
	DrawTexturePro(sliderTexture, srcRec, { sliderPos.x - rect.height / 2, sliderPos.y - rect.height / 2, rect.height, rect.height }, { 0,0 }, 0.0f, WHITE);
	if (IsHovered(*mp))
		DrawRectangleRec(rect, { 100,100,100,150 });
}

Keybinder::Keybinder(int keyID, Rectangle rect, int textSize, std::string name, Texture2D texture)
: module(rect, textSize, name, texture)
{
	this->keyID = keyID;
}

Keybinder::~Keybinder()
{

}

bool Keybinder::IsPressed(Vector2 mp)
{
	if (module::IsPressed(mp))
	{
		ResetKeybinders();
		waitForKey = true;
	}
	return waitForKey;
}

void Keybinder::update()
{
	if (waitForKey)
	{
		int key = GetKeyPressed();
		char keyChar = GetCharPressed();
		bool validKey = false;
		for (int x : possibleKeys)
		{
			if (x == key)
				validKey = true;
		}
		if (key > 47 && key < 58 || key > 64 && key < 91 || key < 301 && key > 289 || validKey)
		{
			AsignKeybind(keyID, key, keyChar);
			waitForKey = false;
		}
	}
	std::string content = "";
	if (keybindsChar[keyID] == '*')
		content += " ";
	else
	{
		switch (keybinds[keyID])
		{
		case KEY_SPACE:
			content += "SPACE";
			break;
		case KEY_TAB:
			content += "TAB";
			break;
		case KEY_LEFT_SHIFT:
			content += "SHIFT";
			break;
		case KEY_LEFT_ALT:
			content += "ALT";
			break;
		case KEY_LEFT_CONTROL:
			content += "CTRL";
			break;
		case KEY_LEFT:
			content += "LEFT";
			break;
		case KEY_RIGHT:
			content += "RIGHT";
			break;
		case KEY_UP:
			content += "UP";
			break;
		case KEY_DOWN:
			content += "DOWN";
			break;
		case KEY_F1:
			content += "F1";
			break;
		case KEY_F2:
			content += "F2";
			break;
		case KEY_F3:
			content += "F3";
			break;
		case KEY_F4:
			content += "F4";
			break;
		case KEY_F5:
			content += "F5";
			break;
		case KEY_F6:
			content += "F6";
			break;
		case KEY_F7:
			content += "F7";
			break;
		case KEY_F8:
			content += "F8";
			break;
		case KEY_F9:
			content += "F9";
			break;
		case KEY_F10:
			content += "F10";
			break;
		case KEY_F11:
			content += "F11";
			break;
		default:
			content += keybindsChar[keyID];
			break;
		}
	}
	this->content = name + ":";
	int length = TextLength(this->content.c_str()) + TextLength(content.c_str());
	while (length < 15)
	{
		this->content += " ";
		length++;
	}
	this->content += content;
}

std::vector<std::unique_ptr<module>> menus[totalMenus];
bool drawMenus[totalMenus];

void UpdateGraphicsMenu()
{
	for (auto&& mod : menus[GRAPHICS_MENU])
	{
		if (mod->name == "Fullscreen")
		{
			if (fw->fullscreen)
				mod->content = "Fullscreen: True";
			else
				mod->content = "Fullscreen: False";
		}
		else if (mod->name == "Borderless")
		{
			if (fw->borderless)
				mod->content = "Borderless: True";
			else
				mod->content = "Borderless: False";
		}
		else if (mod->name == "Resolution")
			mod->content = "Resolution: " + std::to_string(fw->width) + " " + std::to_string(fw->height);
		else if (mod->name == "VSYNC") {
			if (fw->vsync)
				mod->content = "Vsync: True";
			else
				mod->content = "Vsync: False";
		}
		else if (mod->name == "FPS")
			if (fw->fps != 300)
				mod->content = "FPS: " + std::to_string(fw->fps);
			else
				mod->content = "FPS: UNLIMITED";
	}
}

void UpdateMenus()
{
	bool wasPressed = false;
	for (int x = 0; x < totalMenus; x++)
	{
		if (drawMenus[x] && !wasPressed)
		{
			for (auto &&mod : menus[x])
			{
				if (x == GRAPHICS_MENU && wasPressed && mod->name != "Back")
				{
					UpdateGraphicsMenu();
					wasPressed = false;
				}
				if (mod->IsPressed(*mp))
				{
					wasPressed = true;
					mod->update();
				}
			}
		}
	}
}

void DrawMenus()
{
	for (int x = 0; x < totalMenus; x++)
	{
		if (drawMenus[x])
		{
			if (x < 8)
				DrawRectangle(0, 0, 1920, 1080, { 0,0,0,150 });
			for (auto &&mod : menus[x])
			{
				mod->draw();
			}
		}
	}
}

void SetupMainMenu()
{
	menus[MAIN_MENU].emplace_back(new module({860 - 25,528 - 90,250,25}, 15, "New Game"));
	auto&& x = menus[MAIN_MENU][menus[MAIN_MENU].size() - 1].get();
	x->content = "New Game";
	x->AsignFunc([]() {ClearAllMenuStates(); SetMenuState(NEWGAME_MENU); });

	menus[MAIN_MENU].emplace_back(new module({ 860-25,528-60,250,25 }, 15, "Load Game"));
	x = menus[MAIN_MENU][menus[MAIN_MENU].size() - 1].get();
	x->content = "Load Game";
	x->AsignFunc(OpenLoadMenu);

	menus[MAIN_MENU].emplace_back(new module({ 860-25,528-30,250,25 }, 15, "Level Editor"));
	x = menus[MAIN_MENU][menus[MAIN_MENU].size() - 1].get();
	x->content = "Level Editor";
	x->AsignFunc([]() {SetGamestate(LEVEL_EDITOR); ClearAllMenuStates(); });

	menus[MAIN_MENU].emplace_back(new module({ 860-25,528,250,25 }, 15, "Texture Editor"));
	x = menus[MAIN_MENU][menus[MAIN_MENU].size() - 1].get();
	x->content = "Texture Editor";
	x->AsignFunc([]() {SetGamestate(TEXTURE_EDITOR); ClearAllMenuStates(); });

	menus[MAIN_MENU].emplace_back(new module({ 860-25,528+30,250,25 }, 15, "Settings Menu"));
	x = menus[MAIN_MENU][menus[MAIN_MENU].size() - 1].get();
	x->content = "Settings";
	x->AsignFunc(OpenSettings);

	menus[MAIN_MENU].emplace_back(new module({ 860-25,528+60,250,25 }, 15, "Exit"));
	x = menus[MAIN_MENU][menus[MAIN_MENU].size() - 1].get();
	x->content = "Exit";
	x->AsignFunc(QuitGame);
}

void SetupSettingsMenu()
{
	menus[SETTINGS_MENU].emplace_back(new module({ 15, 528 - 90, 250, 25 }, 15, "Graphics"));
	auto&& x = menus[SETTINGS_MENU][menus[SETTINGS_MENU].size() - 1].get();
	x->content = "Graphics";
	x->AsignFunc([]() {ClearAllMenuStates(); SetMenuState(GRAPHICS_MENU); });

	menus[SETTINGS_MENU].emplace_back(new module({ 15,528 - 60,250,25 }, 15, "Sounds"));
	x = menus[SETTINGS_MENU][menus[SETTINGS_MENU].size() - 1].get();
	x->content = "Sounds";
	x->AsignFunc([]() {ClearAllMenuStates(); SetMenuState(SOUND_MENU); });

	menus[SETTINGS_MENU].emplace_back(new module({ 15, 528 - 30, 250, 25 }, 15, "Keybinds"));
	x = menus[SETTINGS_MENU][menus[SETTINGS_MENU].size() - 1].get();
	x->content = "Keybinds";
	x->AsignFunc([]() {ClearAllMenuStates(); SetMenuState(KEYBINDS_MENU); });

	menus[SETTINGS_MENU].emplace_back(new module({ 15, 1080 - 50, 100, 25 }, 15, "Back"));
	x = menus[SETTINGS_MENU][menus[SETTINGS_MENU].size() - 1].get();
	x->content = "Back";
	x->AsignFunc([]() { ClearAllMenuStates(); SetMenuState(MAIN_MENU); });
}

void SetupGraphicsMenu()
{
	menus[GRAPHICS_MENU].emplace_back(new module({ 15, 1080 - 50, 100, 25 }, 15, "Back"));
	auto&& x = menus[GRAPHICS_MENU][menus[GRAPHICS_MENU].size() - 1].get();
	x->content = "Back";
	x->AsignFunc([]() {ClearAllMenuStates(); SetMenuState(SETTINGS_MENU); });

	menus[GRAPHICS_MENU].emplace_back(new ValueModule({ 15, 528 - 90, 250, 25 }, 10, "Resolution", Texture2D(0,0,0,0,0), &fw->width, &fw->height));
	x = menus[GRAPHICS_MENU][menus[GRAPHICS_MENU].size() - 1].get();
	x->update();
	x->AsignFunc(ChangeResolution);

	menus[GRAPHICS_MENU].emplace_back(new module({ 15, 528 - 60, 250, 25 }, 10, "Borderless"));
	x = menus[GRAPHICS_MENU][menus[GRAPHICS_MENU].size() - 1].get();
	x->content = "Borderless";
	x->AsignFunc(SetBorderless);

	menus[GRAPHICS_MENU].emplace_back(new module({ 15, 528 - 30, 250, 25 }, 10, "Fullscreen"));
	x = menus[GRAPHICS_MENU][menus[GRAPHICS_MENU].size() - 1].get();
	x->content = "Fullscreen";
	x->AsignFunc(SetFullscreen);

	menus[GRAPHICS_MENU].emplace_back(new module({ 15, 528, 250, 25 }, 10, "VSYNC"));
	x = menus[GRAPHICS_MENU][menus[GRAPHICS_MENU].size() - 1].get();
	x->content = "Vsync";
	x->AsignFunc([]() {fw->SetupWindow(fw->width, fw->height, fw->fps, fw->fullscreen, fw->borderless, !fw->vsync); SetFPS(); });

	Slider* s = new Slider({ 15, 528 + 30, 250, 25 }, 10, "FPS");
	s->AsignFunc(SetFPS);
	s->SetPointer(&fw->fps);
	s->SetBounds(30, 300);
	menus[GRAPHICS_MENU].emplace_back(s);

	UpdateGraphicsMenu();
}
void SetupSoundsMenu()
{
	menus[SOUND_MENU].emplace_back(new module({ 15, 1080 - 50, 100, 25 }, 15, "Back"));
	auto&& x = menus[SOUND_MENU][menus[SOUND_MENU].size() - 1].get();
	x->content = "Back";
	x->AsignFunc([]() {ClearAllMenuStates(); SetMenuState(SETTINGS_MENU); });

	Slider* s = new Slider({15, 528 - 90, 250, 25}, 10, "MainSound");
	s->SetPointer(nullptr, &fw->mainVolume);
	s->SetBounds(0, 0, 0, 1.0f);
	s->AsignFunc([](){fw->SetupAudio(fw->mainVolume, fw->musicVolume);});
	menus[SOUND_MENU].emplace_back(s);
}
void SetupKeybindsMenu()
{
	menus[KEYBINDS_MENU].emplace_back(new module({ 15, 1080 - 50, 100, 25 }, 15, "Back"));
	auto&& x = menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1].get();
	x->content = "Back";
	x->AsignFunc([]() {ResetKeybinders(); ClearAllMenuStates(); SetMenuState(SETTINGS_MENU); });

	Keybinder* k = new Keybinder(WALK_FORWARD, { 15, 10, 250, 25 }, 15, "Forward");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(WALK_BACKWARDS, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Backwards");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(WALK_LEFT, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Left");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(WALK_RIGHT, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Right");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(INTERACT, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size()-1]->rect.y + 30, 250, 25}, 15, "Interact");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(SPELL_1, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Spell 1");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(SPELL_2, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Spell 2");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(SPELL_3, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Spell 3");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(SPELL_4, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Spell 4");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(SPECIAL, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Special");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(OPEN_INVENTORY, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Inventory");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(USE_ITEM_1, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Item 1");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(USE_ITEM_2, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Item 2");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(USE_ITEM_3, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Item 3");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(USE_ITEM_4, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Item 4");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(CHARGE, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Charge");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(QUICKSAVE, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Quicksave");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);

	k = new Keybinder(QUICKLOAD, { 15, menus[KEYBINDS_MENU][menus[KEYBINDS_MENU].size() - 1]->rect.y + 30, 250, 25 }, 15, "Quickload");
	k->update();
	menus[KEYBINDS_MENU].emplace_back(k);
}
void SetupLoadingMenu()
{}
void SetupSavingMenu()
{}
void SetupGamingUI()
{}
void SetupPlayerInvUI()
{}
void SetupTargetInvUI()
{}
void SetupSmithingUI()
{}
void SetupLeatherworkingUI()
{}
void SetupClothierUI()
{}
void SetupEnchanterUI()
{}
void SetupAlchemistUI()
{}
void SetupDeathscreenMenu()
{}
void SetupIngameMenu()
{
	menus[INGAME_MENU].emplace_back(new module({ 15, 1080 - 75, 100, 25 }, 15, "Exit"));
	auto&& x = menus[INGAME_MENU][menus[INGAME_MENU].size() - 1].get();
	x->content = "Exit Game";
	x->AsignFunc(QuitGame);

	menus[INGAME_MENU].emplace_back(new module({ 15, 1080 - 105, 100, 25 }, 15, "Main"));
	x = menus[INGAME_MENU][menus[INGAME_MENU].size() - 1].get();
	x->content = "Main Menu";
	x->AsignFunc([]() {SetGamestate(MENU); ClearAllMenuStates(); SetMenuState(MAIN_MENU); });
}
void SetupNewGameMenu()
{}

void SetupMenus()
{
	for (int x = 0; x < totalMenus; x++)
	{
		drawMenus[x] = false;
	}
	drawMenus[0] = true;
	SetupMainMenu();
	SetupSettingsMenu();
	SetupGraphicsMenu();
	SetupSoundsMenu();
	SetupKeybindsMenu();
	SetupLoadingMenu();
	SetupSavingMenu();
	SetupGamingUI();
	SetupPlayerInvUI();
	SetupTargetInvUI();
	SetupSmithingUI();
	SetupLeatherworkingUI();
	SetupClothierUI();
	SetupEnchanterUI();
	SetupAlchemistUI();
	SetupDeathscreenMenu();
	SetupIngameMenu();
	SetupNewGameMenu();
	Texture2D Button = LoadTextureFromImage(LoadImage("graphics/MenuButton.png"));
	Texture2D SliderCircle = LoadTextureFromImage(LoadImage("graphics/Slider.png"));
	for (auto&& list : menus)
	{
		for (auto&& mod : list)
		{
			mod->texture = Button;
			Slider* s = dynamic_cast<Slider*>(mod.get());
			if (s)
				s->sliderTexture = SliderCircle;
		}
	}
}

Vector2* mp;
Font f;
