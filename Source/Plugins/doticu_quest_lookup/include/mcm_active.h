/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <unordered_set>

#include "doticu_skylib/quest.h"
#include "doticu_skylib/virtual_latent_id.h"

#include "enum_mcm_view.h"

namespace doticu_skylib { namespace doticu_quest_lookup {

    class MCM_t;

    class MCM_Active_t :
        public Quest_t
    {
    public:
        static constexpr MCM_View_e::value_type DEFAULT_CURRENT_VIEW            = MCM_View_e::LIST;

        static constexpr Int_t                  DEFAULT_LIST_CURRENT_PAGE_INDEX = 0;

        static constexpr size_t                 LIST_ITEMS_PER_PAGE             = 18;

    public:
        class Save_State_t
        {
        public:
            maybe<MCM_View_e>           current_view;

            Int_t                       list_current_page_index;
            Vector_t<Int_t>             list_hidden_objectives;
            Vector_t<maybe<Quest_t*>>   list_objective_quests;

            maybe<Quest_t*>             item_current;

        public:
            Save_State_t();
            Save_State_t(const Save_State_t& other) = delete;
            Save_State_t(Save_State_t&& other) noexcept = delete;
            Save_State_t& operator =(const Save_State_t& other) = delete;
            Save_State_t& operator =(Save_State_t&& other) noexcept = delete;
            ~Save_State_t();

        public:
            Virtual::Variable_tt<String_t>&                     Current_View();

            Virtual::Variable_tt<Int_t>&                        List_Current_Page_Index();
            Virtual::Variable_tt<Vector_t<Int_t>>&              List_Hidden_Objectives();
            Virtual::Variable_tt<Vector_t<maybe<Quest_t*>>>&    List_Objective_Quests();

            Virtual::Variable_tt<maybe<Quest_t*>>&              Item_Current();

        public:
            void    Read();
            void    Write();
        };

        class Option_State_t
        {
        public:
            Int_t   filter;
            Int_t   options;
            Int_t   previous;
            Int_t   next;

        public:
            Option_State_t();
            Option_State_t(const Option_State_t& other) = delete;
            Option_State_t(Option_State_t&& other) noexcept = delete;
            Option_State_t& operator =(const Option_State_t& other) = delete;
            Option_State_t& operator =(Option_State_t&& other) noexcept = delete;
            ~Option_State_t();
        };

        class List_State_t
        {
        public:
            std::unordered_set<Quest_Objective_t*>  hidden_objectives;

        public:
            List_State_t();
            List_State_t(const List_State_t& other) = delete;
            List_State_t(List_State_t&& other) noexcept = delete;
            List_State_t& operator =(const List_State_t& other) = delete;
            List_State_t& operator =(List_State_t&& other) noexcept = delete;
            ~List_State_t();

        public:
            void    Read();
            void    Write();

        public:
            Int_t                               Page_Count(size_t quest_count);
            Int_t                               Current_Page_Index(Int_t page_count);

            Vector_t<some<Quest_t*>>            Quests();
            Vector_t<some<Quest_Objective_t*>>  Objectives(some<Quest_t*> quest);

            Bool_t                              Is_Objective_Hidable(some<Quest_Objective_t*> objective);
            Bool_t                              Is_Objective_Shown(some<Quest_Objective_t*> objective);
            Bool_t                              Is_Objective_Hidden(some<Quest_Objective_t*> objective);

            void                                Show_Objective(some<Quest_Objective_t*> objective);
            void                                Hide_Objective(some<Quest_Objective_t*> objective);

            void                                Enforce_Objectives();
        };

    public:
        static Save_State_t     save_state;
        static Option_State_t   option_state;
        static List_State_t     list_state;

    public:
        static some<MCM_t*>             MCM();

        static some<MCM_Active_t*>      Self();
        static String_t                 Class_Name();
        static some<Virtual::Class_t*>  Class();
        static some<Virtual::Object_t*> Object();

    public:
        static void Reset_Save_State();
        static void Reset_Option_State();
        static void Reset_List_State();

    public:
        static some<MCM_View_e> Current_View();

    public:
        static void On_Register(some<Virtual::Machine_t*> v_machine);

        static void On_After_New_Game();
        static void On_Before_Save_Game();
        static void On_After_Save_Game();
        static void On_Before_Load_Game();
        static void On_After_Load_Game();

        static void On_Update_Version(const Version_t<u16> version_to_update);

    public:
        static void On_Config_Open();
        static void On_Config_Close();

        static void On_Page_Open(Virtual::Latent_ID_t&& latent_id, Bool_t is_refresh);
        static void On_Option_Select(Virtual::Latent_ID_t&& latent_id, Int_t option);
        static void On_Option_Menu_Open(Virtual::Latent_ID_t&& latent_id, Int_t option);
        static void On_Option_Menu_Accept(Virtual::Latent_ID_t&& latent_id, Int_t option, Int_t index);
        static void On_Option_Slider_Open(Virtual::Latent_ID_t&& latent_id, Int_t option);
        static void On_Option_Slider_Accept(Virtual::Latent_ID_t&& latent_id, Int_t option, Float_t value);
        static void On_Option_Input_Accept(Virtual::Latent_ID_t&& latent_id, Int_t option, String_t value);
        static void On_Option_Keymap_Change(Virtual::Latent_ID_t&& latent_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        static void On_Option_Default(Virtual::Latent_ID_t&& latent_id, Int_t option);
        static void On_Option_Highlight(Virtual::Latent_ID_t&& latent_id, Int_t option);

        static void On_Page_Open_List(Virtual::Latent_ID_t&& latent_id, Bool_t is_refresh);

        static void On_Page_Open_Item(Virtual::Latent_ID_t&& latent_id, Bool_t is_refresh);
    };

}}
