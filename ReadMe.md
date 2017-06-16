# 1. 实验名称
指令流水仿真程序

# 2. 实验报告作者
**信息安全 1410658 杨旭东**

# 3. 实验内容
## 3.1. 定义 NK-CPU 指令流水线仿真的基本数据结构
### 3.1.1. 四个锁存器
>nkcpuPipelineDlg.cpp

```c++
// 模拟各段之间的锁存器
// IF/ID
class ifData {
public:
    CString PC;
    CString IR;
    ifData& operator=(ifData x) {
        this->PC = x.PC;
        this->IR = x.IR;
        return *this;
    }
};
ifData ifbefore, ifafter;

// ID/EX
class idData {
public:
    CString PC;
    CString IR;
    int A;
    int B;
    int C;
    int Imm;
    idData& operator=(idData x) {
        this->PC = x.PC;
        this->IR = x.IR;
        this->A = x.A;
        this->B = x.B;
        this->C = x.C;
        this->Imm = x.Imm;
        return *this;
    }
};
idData idbefore, idafter;

// EX/MEM
class exData {
public:
    CString PC;
    CString IR;
    int C;
    int Imm;
    int ALUOutput;
    exData& operator=(exData x) {
        this->PC = x.PC;
        this->IR = x.IR;
        this->ALUOutput = x.ALUOutput;
        this->C = x.C;
        this->Imm = x.Imm;
        return *this;
    }
};
exData exbefore, exafter;

// MEM/WB
class memData {
public:
    CString PC;
    CString IR;
    int Imm;
    int LMD;
    int ALUOutput;
    memData& operator=(memData x) {
        this->PC = x.PC;
        this->IR = x.IR;
        this->ALUOutput = x.ALUOutput;
        this->LMD = x.LMD;
        this->Imm = x.Imm;
        return *this;
    }
};
memData membefore, memafter;
```
五段流水每段之间需要一个锁存器，所以一共是四个分别以锁存器之前的 `段名+Data` 命名，其中：

- `IR` 是该段要处理的指令，
- `PC` 是该指令对应的地址，
- `A` 是指令的 6-10 位也就是操作数 s ，
- `B` 是指令的 11-15 位也就是操作数 t ，
- `C` 是指令的 16-20 位也就是操作数 d ，
- `Imm` 是指令的后 16 位也就是对应的立即数，
- `ALUOutput` 是 EX 段 ALU 运算后的输出结果，
- `LMD` 是 MEM 段取出的数据。

由于没有实现并行操作，是利用串行模拟所以要将锁存器分成两个状态 `××before` 和 `××after` ，每段从 `××before` 读取数据，向 `××after` 写入数据，一个时钟周期结束后将 `××after` 的值赋予 `××before` ，所以我重载了 `=` 运算符。

## 3.2. 使用 C 语言实现 NK-CPU 指令流水线仿真程序
### 3.2.1. 模拟五段流水
设计的总逻辑依据下图：<br>
![](.\readmeImage\4.jpg)<br>
>《计算机体系结构：量化研究方法（第五版）》 P484

#### 3.2.1.1. IF
>nkcpuPipelineDlg.cpp

```c++
CString CnkcpuPipelineDlg::IF() {
    if (ifbefore.IR == "11111111111111111111111111111111") {
        ifafter.IR = ifbefore.IR;
        return _T("NOP");
    }
    else {
        UpdateData(TRUE);
        CString strPC;
        strPC.Format(_T("%d"), m_PC);
        ifafter.PC = strPC;
        m_program.EnsureVisible(m_PC / 4, FALSE);// 滚动到选中行
        m_program.SetItemState(m_PC / 4, LVIS_SELECTED, LVIS_SELECTED);// 高亮选中行，其实未聚焦时为灰色
        CString code = m_program.GetItemText(m_PC / 4, 1);
        ifafter.IR = code.Left(8) + code.Mid(9, 8) + code.Mid(18, 8) + code.Right(8);

        if ((idbefore.IR.Left(6) == "100011"
                && ifbefore.IR.Left(6) == "101011"
                && (idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(6, 5) || idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(11, 5) || idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(16, 5))) ||
            (idbefore.IR.Left(6) == "100011"
                && (ifbefore.IR.Left(6) == "000000" || ifbefore.IR.Left(6) == "100011")
                && (idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(6, 5) || idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(11, 5))) ||
            (idbefore.IR.Left(6) == "100011"
                && (ifbefore.IR.Left(6) == "001000" || ifbefore.IR.Left(6) == "000110")
                && idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(6, 5))) 
        {
            ifafter = ifbefore;
            idafter.IR = _T("000000") + idafter.IR.Mid(6, 20) + _T("000000");
        }
        else if (ifbefore.IR.Left(6) == "000010" || (ifbefore.IR.Left(6) == "000110"&&idafter.A <= 0)) 
        {
            m_PC = idafter.Imm;
            ifafter.IR = _T("000000") + ifafter.IR.Mid(6, 20) + _T("000000");
        }
        else 
        {
            m_PC += 4;
        }
        UpdateData(FALSE);
        return strPC;
    }
}
```
IF 段取指，利用 ID 判断分支是否成立的结果，如果分支指令成立或者是跳转指令，就将 PC 置为相应地址，这里会有一周期的延迟，所以会读入下一条指令，如果跳转到别处，这条指令就没用了，所以将控制位置 0 ，之后的操作也就不会做了。参照下图中的 IF 段：<br>
![](.\readmeImage\1.jpg)<br>
>《计算机体系结构：量化研究方法（第五版）》 P484

还有一点就是在 ID 段由于数据冒险会有旁路转发，其中有一种情况不能处理，也就是载入指令的目标寄存器在紧接着的下一条指令中作为源寄存器被调用，这种情况也会有一周期延迟，这需要停顿等待，其实也是将 ID 段的判断结果在这一段使用。所以我就都写在这一段里了。参照下图中的 表C-11 ：<br>
![](.\readmeImage\2.jpg)<br>
>《计算机体系结构：量化研究方法（第五版）》 P481

如果这两种情况均不存在，就将 PC + 4 存入 PC。

#### 3.2.1.2. ID
>nkcpuPipelineDlg.cpp

```c++
CString CnkcpuPipelineDlg::ID() {
    if (time < 1)return _T("");
    else if (ifbefore.IR.Left(6) == "000000"&&ifbefore.IR.Right(6) == "000000"|| ifbefore.IR == "11111111111111111111111111111111") {
        idafter.IR = ifbefore.IR;
        return _T("NOP");
    }
    else {
        idafter.PC = ifbefore.PC;
        idafter.IR = ifbefore.IR;
        idafter.A = m_Reg[bin2num(ifbefore.IR.Mid(6, 5))];
        idafter.B = m_Reg[bin2num(ifbefore.IR.Mid(11, 5))];
        idafter.C = m_Reg[bin2num(ifbefore.IR.Mid(16, 5))];
        idafter.Imm = bin2num(ifbefore.IR.Right(16));
        if ((memafter.IR.Left(6) == "000000"|| memafter.IR.Left(6) == "100011")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
            && (memafter.IR.Mid(16, 5) == idafter.IR.Mid(6, 5))) {
            if (memafter.IR.Left(6) == "000000")idafter.A = memafter.ALUOutput;
            if (memafter.IR.Left(6) == "100011")idafter.A = memafter.LMD;
        }
        if ((memafter.IR.Left(6) == "000000" || memafter.IR.Left(6) == "100011")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
            && (memafter.IR.Mid(16, 5) == idafter.IR.Mid(11, 5))) {
            if (memafter.IR.Left(6) == "000000")idafter.B = memafter.ALUOutput;
            if (memafter.IR.Left(6) == "100011")idafter.B = memafter.LMD;
        }
        if ((memafter.IR.Left(6) == "000000" || memafter.IR.Left(6) == "100011")
            && (idafter.IR.Left(6) == "101011")
            && (memafter.IR.Mid(16, 5) == idafter.IR.Mid(16, 5))) {
            if (memafter.IR.Left(6) == "000000")idafter.C = memafter.ALUOutput;
            if (memafter.IR.Left(6) == "100011")idafter.C = memafter.LMD;
        }

        if ((memafter.IR.Left(6) == "001000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
            && (memafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
            idafter.A = memafter.ALUOutput;
        }
        if ((memafter.IR.Left(6) == "001000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
            && (memafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
            idafter.B = memafter.ALUOutput;
        }
        if ((memafter.IR.Left(6) == "001000")
            && (idafter.IR.Left(6) == "101011")
            && (memafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
            idafter.C = memafter.ALUOutput;
        }

        if ((memafter.IR.Left(6) == "001111" || memafter.IR.Left(6) == "100000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
            && (memafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
            idafter.A = memafter.Imm;
        }
        if ((memafter.IR.Left(6) == "001111" || memafter.IR.Left(6) == "100000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
            && (memafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
            idafter.B = memafter.Imm;
        }
        if ((memafter.IR.Left(6) == "001111" || memafter.IR.Left(6) == "100000")
            && (idafter.IR.Left(6) == "101011")
            && (memafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
            idafter.C = memafter.Imm;
        }

        if (exafter.IR.Left(6) == "000000"
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
            && (exafter.IR.Mid(16, 5) == idafter.IR.Mid(6, 5))) {
            idafter.A = exafter.ALUOutput;
        }
        if (exafter.IR.Left(6) == "000000"
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
            && (exafter.IR.Mid(16, 5) == idafter.IR.Mid(11, 5))) {
            idafter.B = exafter.ALUOutput;
        }
        if (exafter.IR.Left(6) == "000000"
            && (idafter.IR.Left(6) == "101011")
            && (exafter.IR.Mid(16, 5) == idafter.IR.Mid(16, 5))) {
            idafter.C = exafter.ALUOutput;
        }

        if ((exafter.IR.Left(6) == "001000")////////////////////////
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
            && (exafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
            idafter.A = exafter.ALUOutput;
        }
        if ((exafter.IR.Left(6) == "001000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
            && (exafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
            idafter.B = exafter.ALUOutput;
        }
        if ((exafter.IR.Left(6) == "001000")
            && (idafter.IR.Left(6) == "101011")
            && (exafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
            idafter.C = exafter.ALUOutput;
        }

        if ((exafter.IR.Left(6) == "001111" || exafter.IR.Left(6) == "100000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
            && (exafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
            idafter.A = exafter.Imm;
        }
        if ((exafter.IR.Left(6) == "001111" || exafter.IR.Left(6) == "100000")
            && (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
            && (exafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
            idafter.B = exafter.Imm;
        }
        if ((exafter.IR.Left(6) == "001111" || exafter.IR.Left(6) == "100000")
            && (idafter.IR.Left(6) == "101011")
            && (exafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
            idafter.C = exafter.Imm;
        }

        return ifbefore.PC;
    }
}
```
ID 段译码和访问寄存器取数据，其实都很容易做，主要做的是旁路转发的判断比较繁琐，我基本依据书中的逻辑表编写，因为我的指令设计跟 MIPS 并不完全相同，对相应部分做了修改。逻辑如图：
![](.\readmeImage\3.jpg)<br>
>《计算机体系结构：量化研究方法（第五版）》 P482

#### 3.2.1.3. EX
>nkcpuPipelineDlg.cpp

```c++
CString CnkcpuPipelineDlg::EX() {
    if (time < 2)return _T("");
    else if (idbefore.IR.Left(6) == "000000"&&idbefore.IR.Right(6) == "000000"|| idbefore.IR == "11111111111111111111111111111111") {
        exafter.IR = idbefore.IR;
        return _T("NOP");
    }
    else {
        exafter.PC = idbefore.PC;
        exafter.IR = idbefore.IR;
        exafter.C = idbefore.C;
        exafter.Imm = idbefore.Imm;
        if ((idbefore.IR.Left(6) == "000000"&&idbefore.IR.Right(6) == "100000") ||
            idbefore.IR.Left(6) == "100011" ||
            idbefore.IR.Left(6) == "101011") {
            exafter.ALUOutput = idbefore.A + idbefore.B;
        }
        else if (idbefore.IR.Left(6) == "000000"&&idbefore.IR.Right(6) == "101010") {
            exafter.ALUOutput = idbefore.A < idbefore.B ? 1 : 0;
        }
        else if (idbefore.IR.Left(6) == "001000") {
            exafter.ALUOutput = idbefore.A + idbefore.Imm;
        }           
        return idbefore.PC;
    }
}
```
EX 段运行的指令是要用到 ALU 的指令，我设计的里面有五条，其中：

- add、lw、sw 是寄存器-寄存器加法，
- slt 是寄存器-寄存器比较大小后置位，
- addi 是寄存器-立即数加法，

分别作相应处理即可。

#### 3.2.1.4. MEM
>nkcpuPipelineDlg.cpp

```c++
CString CnkcpuPipelineDlg::MEM() {
    if (time < 3)return _T("");
    else if (exbefore.IR.Left(6) == "000000"&&exbefore.IR.Right(6) == "000000"|| exbefore.IR == "11111111111111111111111111111111") {
        memafter.IR = exbefore.IR;
        return _T("NOP");
    }
    else {
        memafter.PC = exbefore.PC;
        memafter.IR = exbefore.IR;
        memafter.ALUOutput = exbefore.ALUOutput;
        memafter.Imm = exbefore.Imm;
        if (exbefore.IR.Left(6) == "100011") {
            m_datamem.EnsureVisible(exbefore.ALUOutput, FALSE);// 滚动到选中行
            m_datamem.SetItemState(exbefore.ALUOutput, LVIS_SELECTED, LVIS_SELECTED);// 高亮选中行，其实未聚焦时为灰色
            CString numb = m_datamem.GetItemText(exbefore.ALUOutput, 2);
            memafter.LMD = _ttoi(numb);
        }
        else if (exbefore.IR.Left(6) == "101011") {
            CString n;
            n.Format(_T("%d"), exbefore.C);
            m_datamem.EnsureVisible(exbefore.ALUOutput, FALSE);// 滚动到选中行
            m_datamem.SetItemState(exbefore.ALUOutput, LVIS_SELECTED, LVIS_SELECTED);// 高亮选中行，其实未聚焦时为灰色
            m_datamem.SetItemText(exbefore.ALUOutput, 1, num2bin(exbefore.C));
            m_datamem.SetItemText(exbefore.ALUOutput, 2, n);
        }
        return exbefore.PC;
    }
}
```
MEM 段是对存储空间的读写，涉及两条指令：

- lw 是从相应地址取数据，
- sw 是向相应地址写数据，

同样分别作相应处理。

#### 3.2.1.5. WB
>nkcpuPipelineDlg.cpp

```c++
CString CnkcpuPipelineDlg::WB() {
    if (time < 4)return _T("");
    else if (membefore.IR == "11111111111111111111111111111111") { 
        endState = END;
        return _T("NOP");
    }
    else if (membefore.IR.Left(6) == "000000"&&membefore.IR.Right(6) == "000000") {
        return _T("NOP");
    }
    else {
        if (membefore.IR.Left(6) == "000000") {
            m_Reg[bin2num(membefore.IR.Mid(16, 5))] = membefore.ALUOutput;
        }
        else if (membefore.IR.Left(6) == "001000") {
            int a = bin2num(membefore.IR.Mid(11, 5));
            m_Reg[a] = membefore.ALUOutput;
        }
        else if (membefore.IR.Left(6) == "100011") {
            m_Reg[bin2num(membefore.IR.Mid(16, 5))] = membefore.LMD;
        }
        else if (membefore.IR.Left(6) == "001111" || membefore.IR.Left(6) == "100000") {
            m_Reg[bin2num(membefore.IR.Mid(11, 5))] = membefore.Imm;
        }
        UpdateData(FALSE);
        return membefore.PC;
    }
}
```
WB 段是将数据写回寄存器，取锁存器中的相应数据对应指令中相应位置的地址操作即可。<br><br>
另外我在这段设置了程序结束标志，在最后一条结束语句到达 WB 段时运行结束，为的是所有指令均从流水线中排出之后才能停止。

### 3.2.2. 模拟时钟周期
#### 3.2.2.1. 单步执行
>nkcpuPipelineDlg.cpp

```c++
// 使用按钮控制时钟周期，按一次算一个时钟周期
void CnkcpuPipelineDlg::OnBnClickedButton2()
{
    // TODO: 
    if (endState != END) {
        CString t;
        t.Format(_T("%d"), time);
        m_pipeline.InsertItem(0, _T("t") + t);
        m_pipeline.SetItemText(0, 5, WB());//同一个时钟周期，寄存器先写后读
        m_pipeline.SetItemText(0, 4, MEM());//处理lw指令，先写后读
        m_pipeline.SetItemText(0, 3, EX());
        m_pipeline.SetItemText(0, 2, ID());//数据冒险结果存在ID/EX
        m_pipeline.SetItemText(0, 1, IF());
        m_pipeline.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);// 高亮选中行，其实未聚焦时为灰色

        ifbefore = ifafter;
        idbefore = idafter;
        exbefore = exafter;
        membefore = memafter;
        time++;
    }
    else {
        MessageBox(_T("程序执行完毕！"), _T("提示"), MB_ICONINFORMATION);
    }
}
```
按一次按钮对五段做一次操作，并且将每段操作处理的指令的地址输出到程序界面上，NOP 为未做操作。

#### 3.2.2.2. 执行
>nkcpuPipelineDlg.cpp

```c++
void CnkcpuPipelineDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    while (endState != END) {
        OnBnClickedButton2();
    }
    MessageBox(_T("程序执行完毕！"), _T("提示"), MB_ICONINFORMATION);
}
```
程序运行就是重复单步执行操作，直至程序结束。

## 3.3. 仿真运行实验 2 中实现的随机数排序程序
在这部分中，我利用实验二的结果调试写好的流水线，发现之前的汇编的程序也有一些问题，反复更改检查之后才得到正确结果。

## 3.3.1. 更改后的汇编程序
>sort1.asm

```asm
.data
value: .word 29,23,35,50,15,34,5,41,53,13,86,20,4,6,15,71,8,52,19,37
.text
main: add $s7,$zero,$zero
la $a2,value
p1: lw $a0,($a2+$s7)
blez $a0,p6
addi $s6,$s7,1
p2: lw $a0,($a2+$s7)
lw $a1,($a2+$s6)
blez $a1,p3
slt $t0,$a0,$a1
blez $t0,p5
sw $a0,($a2+$s6)
sw $a1,($a2+$s7)
p5: addi $s6,$s6,1
j p2
p3: addi $s7,$s7,1
j p1
p6: #end with a blank line
```

## 3.3.2. 利用实验二得到的机器码和数据存储
### 3.3.2.1. 机器码
>mcode1.txt

```
00000000 00000000 10111000 00100000
10000000 00000110 00000000 00000000
10001100 11010111 00100000 00000000
00011000 10000000 00000000 01000000
00100010 11110110 00000000 00000001
10001100 11010111 00100000 00000000
10001100 11010110 00101000 00000000
00011000 10100000 00000000 00111000
00000000 10000101 01000000 00101010
00011001 00000000 00000000 00110000
10101100 11010110 00100000 00000000
10101100 11010111 00101000 00000000
00100010 11010110 00000000 00000001
00001000 00000000 00000000 00010100
00100010 11110111 00000000 00000001
00001000 00000000 00000000 00001000
11111111 11111111 11111111 11111111
```

### 3.3.2.2. 数据存储
>mdata.txt

```
00000000 00011101
00000000 00010111
00000000 00100011
00000000 00110010
00000000 00001111
00000000 00100010
00000000 00000101
00000000 00101001
00000000 00110101
00000000 00001101
00000000 01010110
00000000 00010100
00000000 00000100
00000000 00000110
00000000 00001111
00000000 01000111
00000000 00001000
00000000 00110100
00000000 00010011
00000000 00100101
```

# 4. 实验设计依据
<p>在计算机硬件的历史上，一些早期的精简指令集计算机中央处理器（RISC CPU）使用了非常相似的架构解决方案，现在称之为经典的 RISC 流水。 那些 CPU 是： MIPS，SPARC，Motorola 88000 和更高版本的 DLX 。</p>
<p>这些经典标量 RISC 设计中的每一个都获取并尝试每个周期执行一个指令。 每个设计的主要常见概念是五阶段执行指令流水线。 在运行期间，每个流水线阶段一次可以在一个指令上工作。</p>
<p>这些阶段中的每一个由初始的触发器组合组成，并且组合逻辑在这些触发器的输出上操作。</p>

## 经典五段 RISC 流水
### *取指*
<p>这些机器上的指令 Cache 有一个周期的延迟。 在指令提取阶段，从缓存中提取了一个 32 位指令。</p>
<p>PC 预测器将程序计数器（PC）发送到指令高速缓存以读取当前指令。 同时，PC 预测器通过将 PC 递增 4（所有指令都是 4 个字节长）来预测下一条指令的地址。 在采取分支，跳跃或异常的情况下，这种预测总是错误的。 后来的机器将使用更复杂和准确的算法来猜测下一个指令地址。</p>

### *译码*
<p>与以前的微型编码机不同，第一台 RISC 机器没有微码。 一旦从指令高速缓存中取出，指令位就沿流水线向下移动，因此每个流水线阶段的简单组合逻辑可以直接从指令位产生数据通路的控制信号。 结果，在传统上称为解码级的阶段中完成了很少的解码。</p>
<p>同时读取寄存器文件，该阶段的指令发出逻辑确定管线是否准备好在该阶段执行指令。 如果不是，问题逻辑将导致指令提取阶段和解码阶段停止。 在一个停顿周期，这些阶段将阻止他们的初始翻牌接受新的比特。</p>
<p>如果解码的指令是分支或跳转，则与读取寄存器文件并行计算分支或跳转的目标地址。 在寄存器文件被读取之后计算分支条件，并且如果分支被采取或者指令是跳转，则第一级中的 PC 预测器被分配分支目标，而不是被计算的增加的 PC。</p>
<p>解码阶段结束了相当多的硬件：如果两个寄存器相等，MIPS 指令集有可能进行分支，因此在寄存器文件读取之后，32 位宽的 AND 树串联运行，使得一个非常长的关键路径 通过这个阶段 此外，分支目标计算通常需要 16 个加法器和 14 位加法器。 在解码阶段解决分支使得可能只有一个单周期分支错误预测的惩罚。 由于分支经常被采取（因此被误用），因此将这一惩罚降低到非常重要。</p>

### *执行*
<p>关于这些简单 RISC 机器的说明可以根据操作类型分为三个等待时间类别：</p>

- 寄存器寄存器操作（单周期延迟）：加，减，比较和逻辑运算。 在执行阶段，两个参数被馈送到一个简单的 ALU，它在执行阶段结束时生成结果。
- 内存参考（两周期延迟）。 所有负载从内存。 在执行阶段，ALU 添加了两个参数（寄存器和常量偏移量），以在循环结束时产生一个虚拟地址。
- 多周期指令（许多周期延迟）。 整数乘法和除法以及所有浮点运算。 在执行阶段，这些操作的操作数被馈送到多周期乘法 / 除法单元。 其余的管道可以自由地继续执行，而倍增 / 分裂单元工作。 为了避免复写阶段和发布逻辑，多周期指令将其结果写入单独的寄存器集。

### *访存*
<p>在这个阶段，单循环延迟指令只需将其结果转发到下一阶段。 此转发确保单循环和两循环指令始终将其结果写入流水线的同一阶段，以便只能使用一个写入端口到寄存器文件，并且始终可用。</p>

### *写回*
<p>在此阶段，单周期和两周期指令将其结果写入寄存器文件。</p>

# 5. 实验结果与分析
## 5.1. 程序界面
![](.\readmeImage\5.jpg)<br>
右侧的数据可以双击更改。
![](.\readmeImage\8.jpg)<br>

## 5.2. 单步执行
![](.\readmeImage\6.jpg)<br>

## 5.3. 执行
![](.\readmeImage\7.jpg)<br>
可以看到程序执行完毕一共用了 2000 多个时钟周期，右侧数据已经由大到小排序完毕。

## 5.4. 程序
参见可执行文件夹中的 nkcpuPipeline.exe ，可以使用。执行结果正确。 

## 5.5. 视频
参见演示视频文件夹，分别对单步执行、执行进行了演示，对修改数据后的执行做了演示。

# 6. 实验心得
远没有想象中的那么简单，流水线的结构设计以及其中出现的冒险情况在听课的时候感觉自己都很清楚的明白，然而实现起来中各个段的逻辑判断很复杂，导致一度陷入困境，从上周就开始设计程序结构，周末着手实现遇到了好多问题，结果好多解决方案都在周一您的课上提到，为此我又重新仔仔细细的研究了一遍书上关于 MIPS 流水的设计方案以及冒险的处理方法。参照它将自己之前的设计几乎全部推翻了，因为实在是理不清头绪，所以索性找了书上清晰地思路重新做，总算是完成了，看着它排序感觉神清气爽。实验越来越难，感觉有些吃力，之后的实验要预习书来做，得多多加油了。

# 7. 参考资料
[1] JohnL.Hennessy, DavidA.Patterson, 亨尼西,等. 计算机体系结构:量化研究方法[M]. 人民邮电出版社, 2013.<br>