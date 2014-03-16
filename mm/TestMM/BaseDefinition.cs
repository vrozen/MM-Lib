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
    class BaseDefinition : Definition
    {
        private static uint n_hitByCreep = 0;
        private static uint n_hitByEssence = 0;

        //tower objects in the game
        private static Dictionary<ulong /*instance*/, Base /*tower*/> bases =
            new Dictionary<ulong, Base>();

        public BaseDefinition(Machine machine)
        {
            m = machine; //static in Definition...
        }

        public void init()
        {
            Machine.CallbackDelegate dCb =
                new Machine.CallbackDelegate(this.definitionCallback);
            uint d_global = m.getGlobalDefinition();
            d_self = m.getElement(d_global, "Base");
            n_hitByEssence = m.getElement(d_self, "hitByEssence");
            n_hitByCreep = m.getElement(d_self, "hitByCreep");
            m.addDefinitionObserver(d_self, /*unsused caller*/ 0, dCb);            
        }

        //create an instance
        public void createInstance(uint instance)
        {
            Base b = new Base(instance);
            bases[instance] = b;
            Machine.CallbackDelegate cb =
              new Machine.CallbackDelegate(this.instanceCallback);
            m.addInstanceObserver(instance, /*not used called*/ 0, cb);
        }

        public void deleteInstance(uint instance)
        {
            bases.Remove(instance);
        }

        public static uint getHitByCreep()
        {
            return n_hitByCreep;
        }

        public static uint getHitByEssence()
        {
            return n_hitByEssence;
        }

        Callback definitionCallback = (caller, message, observable, element, value) =>
        {
            //this callback observes the base definiton (d_base)

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
                // we don't expect any other messages since bases currently don't have child instances
                case MESSAGE.MSG_HAS_VALUE:
                    uint d_pool = element;
                    int value = (int) aux;
                    //instance = instance - 8; //dirty hack... offset bug
                    if (bases.ContainsKey(instance))
                    {
                        Base b = bases[instance];
                        b.setValue(d_pool, value);
                    }
                    else
                    {
                        Console.WriteLine("key not found");
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
