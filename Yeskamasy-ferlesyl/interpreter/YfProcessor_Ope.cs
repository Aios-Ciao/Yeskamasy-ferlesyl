using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace interpreter
{
    partial class YfProcessor
    {
        /// <summary>
        ///     加算命令
        /// </summary>
        /// <param name="eftyp">オペランドタイプ</param>
        /// <param name="efreg1">src側レジスタ</param>
        /// <param name="efreg2">dest側レジスタ</param>
        /// <param name="efval">即値/ラベル値</param>
        public void Op_krz(MOpeland target, MOpeland value)
        {
            ulong temp;

            temp = Load(target);
            temp += Load(value);
            Store(target, temp);
        }
    }
}
