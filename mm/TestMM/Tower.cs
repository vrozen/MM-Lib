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
    class Tower : GameObject
    {
        public Tower(uint instance)
            : base(instance)
        {
        }

        void hitByCreep(Machine m)
        {
            m.activate(i_self, TowerDefinition.getHitByCreep());
        }
    }

}
