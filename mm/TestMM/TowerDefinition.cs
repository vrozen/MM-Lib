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
    class TowerDefinition : Definition
    {
        private static uint d_tower = 0;      //tower definition
        private static uint n_hitByCreep = 0; //node hitByCreep

        //tower objects in the game
        private static Dictionary<ulong /*instance*/, Tower /*tower*/> towers =
            new Dictionary<ulong, Tower>();

        //initializes the definition pointers using the agreed upon name bindings
        public TowerDefinition(Machine machine)
        {
            m = machine; //static in Definition...
        }

        public void init()
        {
            Machine.CallbackDelegate dCb =
                new Machine.CallbackDelegate(this.definitionCallback);
            uint d_global = m.getGlobalDefinition();
            d_tower = m.getElement(d_global, "Tower");
            n_hitByCreep = m.getElement(d_tower, "hitByCreep");
            m.addDefinitionObserver(d_tower, /*unsused caller*/ 0, dCb);
        }

        //create an instance
        public void createInstance(uint instance)
        {
            Tower t = new Tower(instance);
            towers[instance] = t;
            Machine.CallbackDelegate cb =
              new Machine.CallbackDelegate(this.instanceCallback);
            m.addInstanceObserver(instance, /*not used caller*/ 0, cb);
        }

        public void deleteInstance(uint instance)
        {
            towers.Remove(instance);
        }

        public static uint getHitByCreep()
        {
            return n_hitByCreep;
        }

        Callback definitionCallback = (caller, message, observable, element, value) =>
        {
            //this callback observes the tower definiton (d_tower)

            //unfortunately this context is static (this is not available)
            MESSAGE msg = (MESSAGE)message;
            String name = "";

            switch (msg)
            {
                //these are definition level messages we are listening to
                case MESSAGE.MSG_NEW_POOL:
                    name = m.getName(element);
                    setName(element, name);
                    break;
                case MESSAGE.MSG_DEL_POOL:
                    removeName(element);
                    break;
                case MESSAGE.MSG_UPD_POOL:
                    break;

                case MESSAGE.MSG_NEW_CONVERTER:
                    name = m.getName(element);
                    setName(element, name);
                    break;
                case MESSAGE.MSG_DEL_CONVERTER:
                    removeName(element);
                    break;
                case MESSAGE.MSG_UPD_CONVERTER:
                    break;

                case MESSAGE.MSG_NEW_SOURCE:
                    name = m.getName(element);
                    setName(element, name);
                    break;
                case MESSAGE.MSG_DEL_SOURCE:
                    removeName(element);
                    break;
                case MESSAGE.MSG_UPD_SOURCE:
                    break;


                case MESSAGE.MSG_NEW_DRAIN:
                    name = m.getName(element);
                    setName(element, name);
                    break;
                case MESSAGE.MSG_DEL_DRAIN:
                    removeName(element);
                    break;
                case MESSAGE.MSG_UPD_DRAIN:
                    break;
            }
        };

        Callback instanceCallback = (caller, message, instance, element, aux) =>
        {
            //this callback observes instances of type d_tower

            //unfortunately this context is static (this is not available)
            MESSAGE msg = (MESSAGE)message; //message

            switch (msg)
            {
                // we don't expect any other messages since towers currently don't have child instances
                case MESSAGE.MSG_HAS_VALUE:
                    uint d_pool = element;
                    uint value = aux;
                    //instance = instance - 8; //dirty hack... offset bug
                    if(towers.ContainsKey(instance))
                    {
                      Tower tower = towers[instance];
                      tower.setValue(d_pool, value);
                    }
                    else
                    {
                        Console.WriteLine("error finding key");
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
    }

}
