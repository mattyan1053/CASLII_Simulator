# CASL II シミュレータ

大学の計算機高額の授業でアセンブラの勉強をした。  
このときのテスト範囲に、よく情報処理技術者試験で問われるCASL　II準拠の問題がでるらしかったので、暇ついでにシミュレータをC＋＋で作ってみた。  
なにしてんだろうなって自分でも思ったけど残しておく。実装されている命令は次の通り。  

```asemble
    "START"
    "LD"
    "LAD"
    "ST"
    "ADDA"
    "SUBA"
    "AND"
    "OR"
    "XOR"
    "SLA"
    "SRA"
    "SLL"// 中身はSLA
    "SRL"// 中身はSRA
    "CPA"
    "JPL"
    "JMI"
    "JNZ"
    "JZE"
    "JUMP"
    "RET"
    "END"
```
