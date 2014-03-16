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
    class Base : GameObject
    {
        public Base(uint instance)
            : base(instance)
        {
        }

        void hitByCreep(Machine m)
        {
            m.activate(i_self, BaseDefinition.getHitByCreep());
        }

        void hitByEssence(Machine m)
        {
            m.activate(i_self, BaseDefinition.getHitByEssence());
        }
    }
}
