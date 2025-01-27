# include <iostream>
# include <cstdlib>
# include <ctime>
# include <chrono> 
# include <thread> 

/*
角色数据需要拥有HP和MP，金币Coins。 ✅
角色开局选择需要询问是想玩战士，法师还是游侠，来确定初始数值 ✅
角色会被要求进行一项任务，达成目标即可获得胜利
在城镇中，你可以在四个不同的领域展开行动，
在城镇里你可以进行不同的行动 ✅
钓鱼：在钓鱼小游戏中随机获取一个鱼
商店：售卖你的鱼或战利品，购买提升你的能力
许愿：用钱向河神许愿，随机获得或失去钱
战斗：在回合制战斗中磨练你的能力
目前进度
*/

class Character{
    public:
        std::string Name; //名字
        std::string Classname; //名字
        int HP; //力量
        int MP; //智慧
        int Coins; //金币
        
        // 初始化角色数值，在定义怪物和初始角色时使用。

        Character(std::string playername,std::string classname, int hp, int mp, int coins){
            Name = playername;
            Classname = classname; 
            HP = hp;
            MP = mp;
            Coins = coins;
        }

        // 显示角色数据

        void showStatus(){
            std::cout << Classname << Name << "你好\n";
            std::cout << "你的HP为" << HP << "，这决定了你的攻击力和生命值\n";
            std::cout << "你的MP为" << MP << "，这决定了你的法术伤害和法力值\n";
            std::cout << "你的金币数量为" << Coins << "，你可以使用金币来兑换商店的物品\n";
        }
};

Character playerCreateCharacter(){
    std::string playerName;
    int choice;
    
    //让玩家选择名字
    std::cout << "你的名字是什么？\n";
    std::cin >> playerName;

    //让玩家选择职业
    std::cout << "请选择你的职业！\n";
    std::cout << "1. 战士 擅长肉搏和近战攻击的力量角色\n2. 游侠 穿梭在树林中的均衡角色\n";
    std::cout << "3. 法师 擅长法术博览群书的智慧角色\n4. 商人 除了有钱一无是处的经济角色\n";
    std::cin >> choice;

    //选择职业并设定初始数值
    if (choice == 1) {
        return Character(playerName,"战士", 180 , 30 , 50); //战士拥有高力量 低智慧
    }else if (choice == 3) {
        return Character(playerName,"法师", 80 , 150 , 50); //法师拥有低力量 高智慧
    }else if (choice == 2) {
        return Character(playerName,"游侠", 100 , 80 , 50); //游侠拥有中力量 中智慧
    }else {
        return Character(playerName,"商人", 80 , 30 , 300); //商人拥有中力量 低智慧
    }
};

std::string fishReward(){
    const char* garbage[] = {"旧报纸" , "破眼镜" , "垃圾" , "可乐罐" , "破布"};
    const char* commonFish[] = {"金鱼" , "鲤鱼" , "鲈鱼" , "鲢鱼" , "草鱼"};
    const char* rareFish[] = {"大马哈鱼" , "金枪鱼" , "河豚"};
    const char* treasure[] = {"宝藏箱" , "古代项链" , "金戒指"};

    int fishChance = rand() % 100;

    if (fishChance < 20) {
        int i = rand() % (sizeof(garbage) / sizeof(garbage[0]));
        return garbage[i];
    }else if(fishChance < 70) {
        int i = rand() % (sizeof(commonFish) / sizeof(commonFish[0]));
        return commonFish[i];
    }else if(fishChance < 95) {
        int i = rand() % (sizeof(rareFish) / sizeof(rareFish[0]));
        return rareFish[i];
    }else{
        int i = rand() % (sizeof(treasure) / sizeof(treasure[0]));
        return treasure[i];}
}

void fishing (Character &player){
    char choice;
    do {
        //开始钓鱼
        std::cout << player.Name << "来到了河边，开始钓鱼！\n ";

        //设置随机数，1-5秒后上钩
        int waitTime = rand() % 5 + 1 ;
        std::cout << "鱼将在" << waitTime << "秒后上钩，做好准备！\n";

        //等待时间
        std::this_thread::sleep_for(std::chrono::seconds(waitTime));

        //等待结束后咬勾
        std::cout << "鱼上钩了！快在两秒内按下'f'键来拉钩！\n";

        //咬勾时间
        auto startTime = std::chrono::high_resolution_clock::now();
        char input;
        bool success = false;

        //咬勾循环，两秒内若没有输入F则失败，输入则成功
        while((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() < 2) ){
            if (std::cin >> input && input == 'f'){
                success = true;
                break;
            }
        }

        //根据Success变量判断是否上钩
        if(success){
            std::string fishResult = fishReward();
            std::cout << "恭喜！你钓到了: " << fishResult << "！\n";

            //判定战利品，并给予奖励
            if (fishResult == "垃圾"|| fishResult == "可乐罐" || fishResult == "破布"){
                std::cout << "真没素质，往河里丢垃圾！\n";
            }else if(fishResult == "破眼镜"){
                std::cout << "谁掉河里了？\n";
            }else if(fishResult == "旧报纸"){
                std::cout << "这是10年前的新闻啊！\n";
            }else if(fishResult == "金鱼"|| fishResult == "鲤鱼"){
                std::cout << "小鱼也是鱼！\n";
                player.Coins += 10;
            }else if(fishResult == "鲈鱼"){
                std::cout << "是鲈鱼不是鱼露\n";
                player.Coins += 10;
            }else if(fishResult == "鲢鱼"|| fishResult == "草鱼"){
                std::cout << "钓鱼佬永不空军！\n";
                player.Coins += 10;
            }else if(fishResult == "大马哈鱼"|| fishResult == "金枪鱼"){
                std::cout << "好大一条鱼！\n";
                player.Coins += 50;
            }else if(fishResult == "河豚"){
                std::cout << "小心别被扎到了！\n";
                player.Coins += 50;
            }else if(fishResult == "宝藏箱"||fishResult == "古代项链"||fishResult == "金戒指"){
                std::cout << "哇，发财！\n";
                player.Coins += 100;
            }else{
            std::cout << "哎呀，鱼跑掉了！\n";
        }
    }
        //继续钓鱼判定
        std::cout << "是否继续钓鱼？(y/n): ";
        std::cin >> choice;
    }while (choice == 'y' || choice == 'Y');
}

void town (Character &player){
    int move;
    do{
        std::cout << "++++++++++++++++++++\n";
        std::cout << "你现在在鲈鱼镇中，请选择你接下来要去干什么\n";
        std::cout << "++++++++++++++++++++\n";
        std::cout << "1.商店\n";
        std::cout << "2.钓鱼\n";
        std::cout << "3.前去郊外\n";
        std::cout << "4.许愿\n";
        std::cout << "5.查看目前状态\n";
        std::cout << "6.我不玩了\n";
        std::cout << "+++++++++++++++++++++\n";

        //移动
        std::cin >> move;

        //清理缓冲区，避免错误
        std::cin.clear();
        fflush(stdin);
        
        //检测移动，并执行
        switch(move){
            case 1:
                std::cout << "商店系统仍在开发中，敬请期待！\n";
                //shoping(player);
                break;
            case 2:
                std::cout << "正在前往小溪！\n";
                fishing(player);
                break;
            case 3:
                std::cout << "战斗系统仍在开发中，敬请期待！\n";
                //battling(player);
                break;
            case 4:
                std::cout << "许愿系统仍在开发中，敬请期待！\n";
                //wish(player);
                break;
            case 5:
                player.showStatus();
                break;
            case 6:
                std::cout << "下次再玩！\n";
                std::cout << "+++++++++++++++++++++\n";
                break;
            default:
                std::cout << "请输入有效的数字！\n" ;
                break;
        }
    }while (move != 6);
};

int main(){
    //随机数种子
    srand(time(NULL));

    //角色创建模块
    Character player = playerCreateCharacter();
    player.showStatus();

    // 进入城镇
    town(player);

    return 0;
}