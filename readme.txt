1. 代码文件
1.1 头文件
      LexicalScanner.h		词法扫描器头文件
      GrammarParser.h	语法分析器头文件
      QTminiCcompiler.h	交互界面程序头文件
1.2 源文件
      LexicalScanner.cpp	词法扫描器源文件
      GrammarParser.cpp	语法分析器源文件
      QTminiCcompiler.cpp	交互界面程序源文件
      main.cpp		主程序文件
1.3 资源文件
      QTminiCcompiler.ui	交互界面文件
1.4 输出结果文件
      token.txt		词法分析器输出，同时是语法分析器的输入
      --------------------------------------------------------------------------
      FIRST.txt		first集
      FOLLOW.txt		follow集
      grammar0.txt
      grammar1.txt
      grammar2.txt
      ll(1)grammar.txt		ll1文法
      matching_process.txt	匹配token过程
      predictive_table.txt	预测分析表
      syntax_tree.txt		最终结果

2. 已完成内容
目前已经初步完成词法分析和语法分析程序（仍有瑕疵，未能完全完善）