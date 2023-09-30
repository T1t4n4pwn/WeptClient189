#pragma once
#include "globals.h"
#include <Windows.h>

#include "ModuleManager.h"
#include "KeyBoard.h"
#define  IMGUI_DEFINE_MATH_OPERATORS
#include "OwnImGui.h"
#include "utils.h"

#include "custom.hpp"

const char* kName = "WeptClient";
const char* kVersion = "1.3";
const char* kGVersion = "1.8.9";
std::string clickGuiTitle;
std::string authorName = "Author: T1t4n4pwn";
std::string menuUnderlineText;

inline OwnImGui gui("Menu");

void DrawModValues(IModule* mod) {

	auto values = mod->getValues();

	ImGui::Checkbox("Enable", &mod->enable);

	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i].first == BoolType) {
			BoolValue* pValue = (BoolValue*)values[i].second;
			ImGui::Checkbox(pValue->getName().c_str(), pValue->getValuePtr());
			ImGui::NewLine();
		}
		else if (values[i].first == FloatType) {
			FloatValue* pValue = (FloatValue*)values[i].second;
			ImGui::SliderFloat(pValue->getName().c_str(), pValue->getValuePtr(), pValue->getMin(), pValue->getMax(), "%.2f");

			ImGui::NewLine();
		}
		else if (values[i].first == IntType) {
			NumberValue* pValue = (NumberValue*)values[i].second;
			ImGui::SliderInt(pValue->getName().c_str(), (int*)pValue->getValuePtr(), pValue->getMin(), pValue->getMax());
		}
		else if (values[i].first == ListType) {
			ModeValue* pValue = (ModeValue*)values[i].second;
			auto modes = pValue->getModes();
			auto descs = pValue->getDescs();
			ImGui::Combo(pValue->getName().c_str(), pValue->getValuePtr(), pValue->getDescs(), pValue->getModes().size(), 10);

		}
	}

}

#include "custom.hpp"

void GuiCallBack() {

	ModuleManager* pManager = ModuleManager::getInstance();

	for (size_t i = 0; i < pManager->getNumberOfModule(); i++)
	{
		IModule* mod = pManager->getModuleByIndex(i);
		if (mod->isEnable()) {
			mod->onRender();
		}
	}

	IModule* clickGUI = pManager->getModuleByName("ClickGui");
	if (!clickGUI->isEnable()) { return; }

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(510, 380));
	ImGui::Begin(clickGuiTitle.c_str(), NULL, ImGuiWindowFlags_NoTitleBar  | ImGuiWindowFlags_NoCollapse);
	auto window = ImGui::GetCurrentWindow();
	auto draw = window->DrawList;
	auto pos = window->Pos;
	auto size = window->Size;
	auto style = ImGui::GetStyle();

	draw->AddLine(pos + ImVec2(65, 40), pos + ImVec2(size.x - 15, 40), ImColor(1.f, 1.f, 1.f, 0.05f));

	std::vector<IModule*> combatMods = pManager->getModulesByCategory(Category::COMBAT);
	std::vector<IModule*> movementMods = pManager->getModulesByCategory(Category::MOVEMENT);
	std::vector<IModule*> renderMods = pManager->getModulesByCategory(Category::RENDER);
	std::vector<IModule*> worldMods = pManager->getModulesByCategory(Category::WORLD);
	std::vector<IModule*> miscMods = pManager->getModulesByCategory(Category::MISC);

	switch (custom.m_tab) {

	case (int)Category::COMBAT: {
		ImGui::SetCursorPos(ImVec2(70, 13));
		ImGui::BeginGroup();

		for (int i = 0; i < combatMods.size(); ++i) {

			if (custom.sub_tab(combatMods.at(i)->getName().c_str(), custom.m_combat_subtab == i) && custom.m_combat_subtab != i) {
				custom.m_combat_subtab = i, custom.m_anim = 0.f;
			}

			if (i != combatMods.size() - 1) {
				ImGui::SameLine();
			}

		}

		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(65, 50));
		ImGui::BeginChild("##combat_childs", ImVec2(ImGui::GetWindowWidth() - 80, ImGui::GetWindowHeight() - 80)); {
			if (combatMods.size() > 0) {
				DrawModValues(combatMods[custom.m_combat_subtab]);
			}
		}

		ImGui::EndChild();

		break;
	}
	case (int)Category::MOVEMENT: {
		ImGui::SetCursorPos(ImVec2(70, 13));
		ImGui::BeginGroup();

		for (int i = 0; i < movementMods.size(); ++i) {

			if (custom.sub_tab(movementMods.at(i)->getName().c_str(), custom.m_movement_subtab == i) && custom.m_movement_subtab != i)
				custom.m_movement_subtab = i, custom.m_anim = 0.f;

			if (i != movementMods.size() - 1)
				ImGui::SameLine();
		}

		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(65, 50));
		ImGui::BeginChild("##movement_childs", ImVec2(ImGui::GetWindowWidth() - 80, ImGui::GetWindowHeight() - 80)); {

			if (movementMods.size() > 0) {
				DrawModValues(movementMods[custom.m_movement_subtab]);
			}

		}
		ImGui::EndChild();

		break;
	}

	case (int)Category::RENDER: {
		ImGui::SetCursorPos(ImVec2(70, 13));
		ImGui::BeginGroup();

		for (int i = 0; i < renderMods.size(); ++i) {

			if (custom.sub_tab(renderMods.at(i)->getName().c_str(), custom.m_render_subtab == i) && custom.m_render_subtab != i)
				custom.m_render_subtab = i, custom.m_anim = 0.f;

			if (i != renderMods.size() - 1)
				ImGui::SameLine();
		}

		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(65, 50));
		ImGui::BeginChild("##render_childs", ImVec2(ImGui::GetWindowWidth() - 80, ImGui::GetWindowHeight() - 80)); {
			if (renderMods.size() > 0) {
				DrawModValues(renderMods[custom.m_render_subtab]);
			}
		}
		ImGui::EndChild();

		break;
	}

	case (int)Category::WORLD: {
		ImGui::SetCursorPos(ImVec2(70, 13));
		ImGui::BeginGroup();

		for (int i = 0; i < worldMods.size(); ++i) {

			if (custom.sub_tab(worldMods.at(i)->getName().c_str(), custom.m_world_subtab == i) && custom.m_world_subtab != i)
				custom.m_world_subtab = i, custom.m_anim = 0.f;

			if (i != worldMods.size() - 1)
				ImGui::SameLine();
		}

		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(65, 50));
		ImGui::BeginChild("##world_childs", ImVec2(ImGui::GetWindowWidth() - 80, ImGui::GetWindowHeight() - 80)); {
			if (worldMods.size() > 0) {
				DrawModValues(worldMods[custom.m_world_subtab]);
			}
		}
		ImGui::EndChild();

		break;
	}

	case (int)Category::MISC: {
		ImGui::SetCursorPos(ImVec2(70, 13));
		ImGui::BeginGroup();

		for (int i = 0; i < miscMods.size(); ++i) {

			if (custom.sub_tab(miscMods.at(i)->getName().c_str(), custom.m_misc_subtab == i) && custom.m_misc_subtab != i)
				custom.m_misc_subtab = i, custom.m_anim = 0.f;

			if (i != miscMods.size() - 1)
				ImGui::SameLine();
		}

		ImGui::EndGroup();

		ImGui::SetCursorPos(ImVec2(65, 50));
		ImGui::BeginChild("##misc_childs", ImVec2(ImGui::GetWindowWidth() - 80, ImGui::GetWindowHeight() - 80)); {
			if (miscMods.size() > 0) {
				DrawModValues(miscMods[custom.m_misc_subtab]);
			}
		}
		ImGui::EndChild();

		break;
	}

}

	ImGui::SetCursorPosY(0);
	custom.tab_area("##tab_area", ImVec2(50, size.y - 20), []() {

		for (int i = 0; i < custom.tabs.size(); ++i)
			if (custom.tab(custom.tabs_icons.at(i), custom.tabs.at(i), custom.m_tab == i) && custom.m_tab != i)
				custom.m_tab = i, custom.m_anim = 0.f;

		});

	// footer
	
	draw->AddRectFilled(pos + ImVec2(0, size.y - 20), pos + size, ImColor(15, 14, 21), style.WindowRounding, ImDrawFlags_RoundCornersBottom);
	draw->AddText(pos + ImVec2(5, size.y - 18), ImGui::GetColorU32(ImGuiCol_Text), menuUnderlineText.c_str());
	draw->AddText(pos + ImVec2(size.x - ImGui::CalcTextSize(authorName.c_str()).x - 5, size.y - 18), ImColor(255, 215, 0), authorName.c_str());


	ImGui::End();
	ImGui::PopStyleVar(2);

}

void GuiThread() {

	clickGuiTitle.append(kName);
	clickGuiTitle.append(" | ");
	clickGuiTitle.append(kVersion);

	menuUnderlineText.append(kName)
		.append(" | ")
		.append("Minecraft ")
		.append(kGVersion);

	WindowInfo info = GetWindowInfoByPID(GetCurrentProcessId());
	
	gui.Start(info.ClassName.c_str(), info.Caption.c_str(), GuiCallBack);
}

#include "Sprint.h"
#include "ClickGui.h"
#include "AimBot.h"
#include "Reach.h"
#include "ESP.h"
#include "TestMod.h"
#include "AutoClicker.h"
#include "Teams.h"

#include "Wetp.h"

static int HackMain() {

	Wept wept;
	std::string version = wept.get_version();
	if (version.compare(kVersion) != 0) {
		std::cout << "当前版本: " << kVersion << " | " << "最新版本: " << version << std::endl;
		std::cout << "版本过期， 请更新到最新版" << std::endl;
		getchar();
		return -1;
	}

	while (!hasInitialize) {
		Sleep(100);
	}

	jint res = g_vm->GetEnv((void**)&g_env, JNI_VERSION_1_8);
	if (res == JNI_EDETACHED)
	{
		res = g_vm->AttachCurrentThreadAsDaemon((void**)&g_env, nullptr);
	}


	if (res != JNI_OK)

	{
		MessageBoxA(0, "AttachCurrentThreadAsDaemon Failed!", "Error", 0);
	}

	forgeCache.InitCache();

	ModuleManager* manager = ModuleManager::getInstance();

	//COMBAT
	manager->addModule(new AimBot);
	manager->addModule(new Reach);
	manager->addModule(new AutoClicker);
	manager->addModule(new TestMod);
	//MOVMENT
	manager->addModule(new Sprint);

	//RENDER
	manager->addModule(new ClickGui);

	//MISC
	manager->addModule(new Teams);
	//manager->addModule(new ESP);
	

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyBoard::StartListen, 0, 0, 0);
	HANDLE hGuiThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GuiThread, 0, 0, 0);
	SetThreadPriority(hGuiThread, THREAD_PRIORITY_HIGHEST);
	manager->invokeAll();

	return 0;
}