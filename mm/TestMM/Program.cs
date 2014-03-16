using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;
using LibMM;
using System.Security;
using System.Diagnostics;

namespace TestMM
{
    [SuppressUnmanagedCodeSecurity]
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    delegate void Callback(uint caller,
                           uint message,
                           uint instance,
                           uint element,
                           uint value);

    class Program
    {
        //pointers to definitions (d), nodes such as pools (p) and instances (i)
        private static uint d_global = 0;  //global definition
        private static uint i_global = 0;  //global instance
        private static uint p_towers = 0;  //towers pool
        private static uint p_creeps = 0;  //creeps pool
        private static uint p_bases = 0;   //bases pool
        private static uint p_gold = 0;    //gold pool
        private static uint p_essence = 0; //essence pool
        private static uint d_base = 0;    //base definition
        private static uint d_tower = 0;   //towers definition

        private static uint n_spawn = 0;
        private static uint n_missed = 0;
        private static uint n_buyTower = 0;
        private static uint n_buyBase = 0;

        //we also store values (v) locally, although this isn't really necessary since we have events
        private static int v_towers = 0;   //amount of towers
        private static int v_bases = 0;    //amount of bases
        private static int v_essence = 0;  //amount of essence
        private static int v_creeps = 0;   //amount of creeps
        private static int v_gold = 0;     //amount of gold


        private static BaseDefinition b;
        private static TowerDefinition t;

        private static Machine m;

        //initializes the definition pointers using the agreed upon name bindings
        public Program(Machine machine)
        {
            m = machine;
        }

        public void init()
        {
            Machine.CallbackDelegate gICb = new Machine.CallbackDelegate(this.instanceCallback);

            Machine.CallbackDelegate gDCb = new Machine.CallbackDelegate(this.definitionCallback);

            d_global = m.getGlobalDefinition();
            i_global = m.getGlobalInstance();

            m.addDefinitionObserver(d_global, 0 /*caller not yet used*/, gDCb);
            m.addInstanceObserver(i_global, 0 /*caller not yet used*/, gICb);

            p_towers = m.getElement(d_global, "towers");
            p_bases = m.getElement(d_global, "bases");
            p_gold = m.getElement(d_global, "gold");
            p_creeps = m.getElement(d_global, "creeps");
            p_essence = m.getElement(d_global, "essence");

            d_base = m.getElement(d_global, "Base");
            d_tower = m.getElement(d_global, "Tower");

            n_spawn = m.getElement(d_global, "spawn");
            n_missed = m.getElement(d_global, "missed");
            n_buyTower = m.getElement(d_global, "buyTower");
            n_buyBase = m.getElement(d_global, "buyBase");

            b = new BaseDefinition(m);
            b.init();

            t = new TowerDefinition(m);
            t.init();
        }


        /*Physics: user actions*/
        public void spawn()
        {
            m.activate(n_spawn, i_global);
        }

        public void miss()
        {
            m.activate(n_missed, i_global);
        }

        /*Menu: user actions*/
        public void buyTower()
        {
            m.activate(n_buyTower, i_global);
        }

        public void buyBase()
        {
            m.activate(n_buyBase, i_global);
        }

        private static void setTowers(int value)
        {
            v_towers = value;
        }

        private static void setBases(int value)
        {
            v_bases = value;
        }

        private static void setCreeps(int value)
        {
            v_creeps = value;
        }

        private static void setEssence(int value)
        {
            v_essence = value;
        }

        private static void setGold(int value)
        {
            v_gold = value;
        }

        Callback definitionCallback = (caller, message, instance, element, aux) =>
        {
            //we currently do not process updates to the global type
            //although those might be useful to add to a global menu?
        };

        Callback instanceCallback = (caller, message, instance, element, aux) =>
        {
            //this callback observes instances of type d_tower

            //unfortunately this context is static (this is not available)
            MESSAGE msg = (MESSAGE)message; //message

            uint i_child = 0;
            uint d_child = 0;
            d_base = m.getElement(d_global, "Base");
            d_tower = m.getElement(d_global, "Tower");


            switch (msg)
            {
                case MESSAGE.MSG_NEW_INST:
                    i_child = element;
                    d_child = aux;

                    if (d_child == d_tower)
                    {
                        b.createInstance(i_child);
                    }
                    else if (d_child == d_base)
                    {
                        t.createInstance(i_child);
                    }
                    break;
                case MESSAGE.MSG_DEL_INST:
                    i_child = element;
                    d_child = aux;

                    if (d_child == d_tower)
                    {
                        b.deleteInstance(i_child);
                    }
                    else if (d_child == d_base)
                    {
                        t.deleteInstance(i_child);
                    }
                    break;
                case MESSAGE.MSG_HAS_VALUE:
                    uint pool = element;
                    int value = (int) aux;
                    if (pool == p_towers)
                    {
                        setTowers(value);
                    }
                    else if (pool == p_bases)
                    {
                        setBases(value);
                    }
                    else if (pool == p_essence)
                    {
                        setEssence(value);
                    }
                    else if (pool == p_gold)
                    {
                        setGold(value);
                    }
                    else if (pool == p_creeps)
                    {
                        setCreeps(value);
                    }
                    break;
                case MESSAGE.MSG_SUB_VALUE:
                    //not currently used but works like MSG_HAS_VALUE
                    //except that all nodes are included, not just pools
                    break;
                case MESSAGE.MSG_ADD_VALUE:
                    //not currently used but works like MSG_HAS_VALUE
                    //except that all nodes are included, not just pools
                    break;
            }
        };



        static void Main(string[] args)
        {
            Machine m = new Machine();
            Program p = new Program(m);

            //m.evalFile("C:\\Users\\rozen\\Documents\\Visual Studio 2010\\Projects\\mm\\tests\\test.mm");

            String modelsDir = "C:\\Users\\rozen\\Documents\\Visual Studio 2010\\Projects\\mm\\tests\\towers\\";

            m.evalFile(modelsDir + "mod1_fig7_tower1.mm");
            m.evalFile(modelsDir + "mod2_fig8_base1.mm");
            m.evalFile(modelsDir + "mod3_fig6_world.mm");
            m.evalFile(modelsDir + "mod4_fig9_tower2.mm");
            m.evalFile(modelsDir + "mod5_fig10_base2.mm");
            m.evalFile(modelsDir + "mod6_fig11_tower3.mm");
            m.evalFile(modelsDir + "mod7_fig12_base3.mm");
            m.evalFile(modelsDir + "mod8_fig13_tower4.mm");            
            
            p.init(); //every time we update definitions

            Stopwatch sw = System.Diagnostics.Stopwatch.StartNew();

            p.buyTower();
            p.buyBase();

            for (int i = 0; i < 1000000; i++)
            {
                sw.Start();
                m.step();  //a model only makes a step when you tell it to
                sw.Stop();
                double cur = (double)sw.Elapsed.TotalMilliseconds;
                sw.Reset();

                p.spawn();

                p.miss();

                Console.Write("\r{0} bases {1} towers {2}\tessence {3}\tcreeps {4}\tgold {5}",
                                (cur).ToString("\r0.00\tms"),
                                v_bases, v_towers, v_essence, v_creeps, v_gold);
            }

            m.reset();

            Console.WriteLine();


        }
    }
}
