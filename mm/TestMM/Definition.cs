using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using LibMM;

namespace TestMM
{
    class Definition
    {
        protected static uint d_self; //definition
        protected static Machine m;
        private static Dictionary<ulong /*n_node*/, String /*name*/> names =
            new Dictionary<ulong, string>();

        public static void setName(ulong n_node, String name)
        {
            names[n_node] = name;
        }

        public static void removeName(ulong n_node)
        {
            names.Remove(n_node);
        }

        public static String getName(ulong n_node)
        {
            if(names.ContainsKey(n_node))
            {
                return names[n_node]; 
            }
            else
            {
                return "undefined";
            }
        }

        public static String toString()
        {
            String r = "{";

            foreach(KeyValuePair<ulong, string> item in names)
            {
                r += item.Value + " ";
            }

            r += "}";
            return r;
        }
    }
}
