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
    class GameObject
    {
        protected uint i_self;

        private Dictionary<ulong /*n_pool*/, long /*value*/> values =
             new Dictionary<ulong, long>();

        public GameObject(uint instance)
        {
            i_self = instance;
        }

        //you can actually activate any node
        //so if the definition found a new node
        //the activate function can activate that node for you
        void activate(Machine m, uint n_node)
        {
            m.activate(i_self, n_node);
        }

        public long getValue(ulong n_pool)
        {
            long r = 0;
            if (values.ContainsKey(n_pool))
            {
                r = values[n_pool];
            }
            return r;
        }

        public void setValue(ulong n_pool, long value)
        {
            values[n_pool] = value;
        }
    }
}
