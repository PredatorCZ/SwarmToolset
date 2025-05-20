/*translation of the methcall test from The Great Computer Language Shootout
*/

class Toggle {
    bool=null
} 

function Toggle::constructor(startstate) {
    bool = startstate
}

function Toggle::value() {
    return bool; 
}

function Toggle::activate() {
    bool = !bool;
    return this;
}

class NthToggle extends Toggle {
    count_max=null
    count=0
}

function NthToggle::constructor(start_state,max_counter)
{
    base.constructor(start_state);
    count_max = max_counter
}

function NthToggle::activate ()
{
    ++count;
    if (count >= count_max ) {
      base.activate();
      count = 0;
    }  
    return this;
}


function main() {
    local n = vargv.len()!=0?vargv[0].tointeger():1

    local cls = NthToggle;
    local arr = [1, 2, 3, 4,  8,5 ,6 , 7];
    local val = 1;
    local toggle = Toggle(val);
    local i = n;
    while(i--) {
      val = toggle.activate().value();

    }
    print(toggle.value() ? "true\n" : "false\n");
    val = 1;
    local ntoggle = NthToggle(val, 3);
    i = n;
    while(i--) {
      val = ntoggle.activate().value();
    }
    print(ntoggle.value() ? "true\n" : "false\n");

}
local start=clock();
main();
print("TIME="+(clock()-start)+"\n");


const OUTLINE_SIZE = 2
//local OUTLINE_MID = OUTLINE_SIZE / 2

local FOOTER_LU = ImVec2(0, 690) + ImVec2(OUTLINE_SIZE, -OUTLINE_SIZE)
local FOOTER_RU = ImVec2(1280, 690) - OUTLINE_SIZE
local FOOTER_RD = ImVec2(1280, 720) - OUTLINE_SIZE
local FOOTER_LD = ImVec2(0, 720) + ImVec2(OUTLINE_SIZE, -OUTLINE_SIZE)

local HEADER_LU = ImVec2(0, 0) + OUTLINE_SIZE
local HEADER_RU = ImVec2(1280, 0) - ImVec2(OUTLINE_SIZE, -OUTLINE_SIZE)
local HEADER_RD = ImVec2(1280 - OUTLINE_SIZE, 45)
const HEADER_MIDPOINT_OFFSET = 200
local HEADER_MIDPOINT_P1 = ImVec2(HEADER_MIDPOINT_OFFSET, 90)
local HEADER_MIDPOINT_P2 = ImVec2(HEADER_MIDPOINT_OFFSET + 70, 40)
local HEADER_MIDPOINT_P3 = ImVec2(HEADER_MIDPOINT_OFFSET + 180, 45)
local HEADER_LD = ImVec2(OUTLINE_SIZE, 90)


local BIRD_VERTICES_WINGS = [
    ImVec2(8,32),
    ImVec2(-8,32),
    ImVec2(-42,16),
    ImVec2(-46,6),
    ImVec2(-8,13),
    ImVec2(8,13),
    ImVec2(46,6),
    ImVec2(42,16),
]

local BIRD_VERTICES_BODY = [
    ImVec2(-3,69),
    ImVec2(-7,68),
    ImVec2(-8,63),
    ImVec2(-4,61),
    ImVec2(-8,31),
    ImVec2(8,31),
    ImVec2(4,61),
    ImVec2(8,63),
    ImVec2(7,68),
    ImVec2(3,69),
    ImVec2(2,73),
    ImVec2(-2,73),
]

local BIRD_VERTICES_FEATHER1 = [
    ImVec2(-22,25),
    ImVec2(-20,34),
    ImVec2(-17,36),
    ImVec2(-17,27),
]

local BIRD_VERTICES_FEATHER0 = [
    ImVec2(-32.5,20),
    ImVec2(-30.5,29),
    ImVec2(-28,31),
    ImVec2(-28,22.5),
]

local BIRD_VERTICES_FEATHER0_M = [
    ImVec2(32.5,20),
    ImVec2(30.5,29),
    ImVec2(28,31),
    ImVec2(28,22.5),
]

local BIRD_VERTICES_FEATHER1 = [
    ImVec2(-22,25),
    ImVec2(-20,34),
    ImVec2(-17,36),
    ImVec2(-17,27.5),
]

local BIRD_VERTICES_FEATHER1_M = [
    ImVec2(22,25),
    ImVec2(20,34),
    ImVec2(17,36),
    ImVec2(17,27.5),
]

local BIRD_VERTICES_HEAD = [
    ImVec2(-10, 5),
    ImVec2(-14, 8),
    ImVec2(-13, 10),
    ImVec2(-13, 9),
    ImVec2(-9, 6),
    ImVec2(-6, 13),
    ImVec2(9, 13),
    ImVec2(0, 0),
]

local BIRD_OUTLINE = [
    BIRD_VERTICES_WINGS[4],
    BIRD_VERTICES_WINGS[3],
    BIRD_VERTICES_WINGS[2],
    BIRD_VERTICES_FEATHER0[0],
    BIRD_VERTICES_FEATHER0[1],
    BIRD_VERTICES_FEATHER0[2],
    BIRD_VERTICES_FEATHER0[3],
    BIRD_VERTICES_FEATHER1[0],
    BIRD_VERTICES_FEATHER1[1],
    BIRD_VERTICES_FEATHER1[2],
    BIRD_VERTICES_FEATHER1[3],
    BIRD_VERTICES_WINGS[1],
    BIRD_VERTICES_BODY[3],
    BIRD_VERTICES_BODY[2],
    BIRD_VERTICES_BODY[1],
    BIRD_VERTICES_BODY[0],
    BIRD_VERTICES_BODY[11],
    BIRD_VERTICES_BODY[10],
    BIRD_VERTICES_BODY[9],
    BIRD_VERTICES_BODY[8],
    BIRD_VERTICES_BODY[7],
    BIRD_VERTICES_BODY[6],
    BIRD_VERTICES_WINGS[0],
    BIRD_VERTICES_FEATHER1_M[3],
    BIRD_VERTICES_FEATHER1_M[2],
    BIRD_VERTICES_FEATHER1_M[1],
    BIRD_VERTICES_FEATHER1_M[0],
    BIRD_VERTICES_FEATHER0_M[3],
    BIRD_VERTICES_FEATHER0_M[2],
    BIRD_VERTICES_FEATHER0_M[1],
    BIRD_VERTICES_FEATHER0_M[0],
    BIRD_VERTICES_WINGS[7],
    BIRD_VERTICES_WINGS[6],
    BIRD_VERTICES_HEAD[6],
    BIRD_VERTICES_HEAD[7],
    BIRD_VERTICES_HEAD[0],
    BIRD_VERTICES_HEAD[1],
    BIRD_VERTICES_HEAD[2],
    //BIRD_VERTICES_HEAD[3],
    //BIRD_VERTICES_HEAD[4],
    //BIRD_VERTICES_HEAD[5],
]

local U_COL = 0xff8f8c85;
local L_COL = 0xff8f8c85;
local B_COL = 0xff2b271c;
local R_COL = 0xff2b271c;

local BIRD_OUTLINE_COLORS = [
    U_COL,
    L_COL,
    B_COL,
    L_COL,
    B_COL,
    R_COL,
    B_COL,
    L_COL,
    B_COL,
    R_COL,
    B_COL,
    L_COL,
    U_COL,
    L_COL,
    B_COL,
    L_COL,
    B_COL,
    R_COL,
    B_COL,
    R_COL,
    U_COL,
    R_COL,
    B_COL,
    L_COL,
    B_COL,
    R_COL,
    B_COL,
    L_COL,
    B_COL,
    R_COL,
    B_COL,
    R_COL,
    U_COL,
    R_COL,
    U_COL,
    U_COL,
    L_COL,
    L_COL,
]

// REFAC move to class with update and AddConcavePolyFilled
function ImDrawList::DrawBird(color, offset, size) {
    foreach(i,v in BIRD_VERTICES_WINGS) {
        this.PathLineTo(offset + v * size, color)
    }

    this.PathFillConvex()

    foreach(i,v in BIRD_VERTICES_BODY) {
        this.PathLineTo(offset + v * size, color)
    }

    this.PathFillConvex()

    foreach(i,v in BIRD_VERTICES_FEATHER0) {
        this.PathLineTo(offset + v * size, color)
    }

    this.PathFillConvex()

    foreach(i,v in BIRD_VERTICES_FEATHER0_M) {
        this.PathLineTo(offset + v * size, color)
    }

    this.PathFillConvex()

    foreach(i,v in BIRD_VERTICES_FEATHER1) {
        this.PathLineTo(offset + v * size, color)
    }

    this.PathFillConvex()

    foreach(i,v in BIRD_VERTICES_FEATHER1_M) {
        this.PathLineTo(offset + v * size, color)
    }

    this.PathFillConvex()

    this.PathLineTo(offset + BIRD_VERTICES_HEAD[0] * size, color)
    this.PathLineTo(offset + BIRD_VERTICES_HEAD[1] * size, color)
    this.PathLineTo(offset + BIRD_VERTICES_HEAD[2] * size, color)
    this.PushColor(color)
    this.PathBezierCubicCurveTo(
        offset + BIRD_VERTICES_HEAD[3] * size, 
        offset + BIRD_VERTICES_HEAD[4] * size, 
        offset + BIRD_VERTICES_HEAD[5] * size)
    this.PathLineTo(offset + BIRD_VERTICES_HEAD[6] * size, color)
    this.PathLineTo(offset + BIRD_VERTICES_HEAD[7] * size, color)
    this.PathFillConvex()
    this.PopColor()
    
    
    foreach(i,v in BIRD_OUTLINE) {
        this.PathLineTo(offset + v * size, BIRD_OUTLINE_COLORS[i])
    }

    this.PushColor(L_COL)
    this.PathBezierCubicCurveTo(
        offset + BIRD_VERTICES_HEAD[3] * size, 
        offset + BIRD_VERTICES_HEAD[4] * size, 
        offset + BIRD_VERTICES_HEAD[5] * size)
    this.PopColor()
    this.PathStroke(0x201, 0.7 * size)
}

local curval = 120

local GLOBE_HLINES = [
    [ImVec2(20, 175), ImVec2(180, 180)],
    [ImVec2(0, 150), ImVec2(200, 155)],
    [ImVec2(0, 125), ImVec2(200, 130)],
    [ImVec2(0, 97), ImVec2(200, 103)],
    [ImVec2(0, 75), ImVec2(200, 70)],
    [ImVec2(0, 45), ImVec2(200, 50)],
    [ImVec2(20, 25), ImVec2(180, 30)],
]


function ImDrawList::DrawGlobe(color, offset, size) {
    foreach(i, v in GLOBE_HLINES) {
        this.AddRectFilled(offset + v[0] * size, offset + v[1] * size, color, color, color, color)
    }

    curval += 1.5
    
    for(local i = 0; i < 5; i++) {
        local bounds = 260
        local curVal = (curval + 50 * i) % bounds
        local curVPos0 = 95 + ((curval + 50 * i) % bounds) - 125
        local curThc0 = (curVal - 130) / 35.0
        local curVPos1 = curVPos0 - curThc0
        
        local p2y = 30;
        local p3y = 170;

        this.AddBezierCubic(offset + ImVec2(100, 5) * size,offset + ImVec2(curVPos0, p2y) * size, offset + ImVec2(curVPos0, p3y) * size, offset + ImVec2(100, 195) * size, color, 5 * size)
        //this.AddBezierCubic(offset + ImVec2(100, 5) * size,offset + ImVec2(curVPos1, p2y) * size, offset + ImVec2(curVPos1, p3y) * size, offset + ImVec2(100, 195) * size, 0xff888888, fabs(curThc0) * size)
    }
    

    this.PathLineTo(offset + ImVec2(200, 0) * size)
    this.PathArcTo(offset + ImVec2(100, 100) * size, 90 * size, 0, -PI)
    this.PathLineTo(offset + ImVec2(0, 0))
    this.PathFillConcave()
    this.PathLineTo(offset + ImVec2(0, 200) * size)
    this.PathArcTo(offset + ImVec2(100, 100) * size, 90 * size, PI, 0)
    this.PathLineTo(offset + ImVec2(200, 200) * size)
    this.PathFillConcave()

    this.PathLineTo(offset + ImVec2(10, 100) * size)
    this.PathLineTo(offset + ImVec2(0, 0))
    this.PathLineTo(offset + ImVec2(0, 200) * size)
    this.PathFillConcave()

    this.PathLineTo(offset + ImVec2(200, 200) * size)
    this.PathLineTo(offset + ImVec2(200, 0) * size)
    this.PathLineTo(offset + ImVec2(190, 100) * size)
    this.PathFillConcave()
}

function UI::OnDraw(drawList) {
    /*drawList.AddCircle(ImVec2(10, 10), 5, 0xff00ffff)
    drawList.AddBezierCubic(ImVec2(10, 10), 
    ImVec2(70, 40) * 0.1,
    ImVec2(70, 80),
    ImVec2(10, 120), 0xffff00ff, 2, 30)
    local clr = 0xff00ffff*/

    //drawList.AddBezierQuadratic(ImVec2(coffset, 90),ImVec2(coffset + 50, 40), ImVec2(coffset + 180, 45), 0xffffffff, 3)
    
    drawList.PushColorArea(HEADER_LU, FOOTER_RU, 0xff19160b, 0xffbdb08d, 0xffbdb08d, 0xff19160b)
    drawList.PathLineTo(HEADER_LU, 0xff19160b)
    drawList.PathLineTo(HEADER_RU, 0xffbdb08d)
    drawList.PathLineTo(HEADER_RD, 0xffbdb08d)
    drawList.PathBezierCubicCurveTo(HEADER_MIDPOINT_P3, HEADER_MIDPOINT_P2, HEADER_MIDPOINT_P1)
    drawList.PathLineTo(HEADER_LD, 0xff19160b)
    drawList.PathFillConvex()
    drawList.DrawGlobe(0xff8f7050, ImVec2(60, 5), 0.4)
    drawList.PopColorArea()
    
    
    drawList.DrawBird(0xff403e35, ImVec2(100, 15), 0.9)
    
    drawList.AddLine(HEADER_LU, HEADER_LD, 0xff4f4c45, 0xff4f4c45, OUTLINE_SIZE)
    drawList.AddLine(HEADER_LD, HEADER_MIDPOINT_P1, 0xff3b372c, 0xff3b372c, OUTLINE_SIZE)
    drawList.AddLine(HEADER_LU, HEADER_RU, 0xffc1beb3, 0xffc1beb3, OUTLINE_SIZE)
    drawList.AddLine(HEADER_RU, HEADER_RD, 0xff3b372c, 0xff3b372c, OUTLINE_SIZE)
    drawList.AddBezierCubic(HEADER_MIDPOINT_P1, HEADER_MIDPOINT_P2, HEADER_MIDPOINT_P3, HEADER_RD, 0xff3b372c, OUTLINE_SIZE+1)
    drawList.AddRectFilled(FOOTER_LU, FOOTER_RD, 
    0xff19160b,
    0xffbdb08d, 
    0xffbdb08d, 
    0xff19160b)
    

    drawList.AddLine(FOOTER_LD, FOOTER_LU, 0xff4f4c45,0xff4f4c45, OUTLINE_SIZE)
    drawList.AddLine(FOOTER_LU, FOOTER_RU, 0xffc1beb3,0xffc1beb3, OUTLINE_SIZE)
    drawList.AddLine(FOOTER_RU,FOOTER_RD, 0xff3b372c,0xff3b372c, OUTLINE_SIZE)
    drawList.AddLine(FOOTER_LD,FOOTER_RD, 0xff3b372c,0xff3b372c, OUTLINE_SIZE)
    
    
    
    /*local globeColor = 0xff8f7050
    
    drawList.AddRectFilled(ImVec2(220, 375), ImVec2(380, 380), globeColor, globeColor, globeColor, globeColor)
    drawList.AddRectFilled(ImVec2(200, 350), ImVec2(400, 355), globeColor, globeColor, globeColor, globeColor)
    drawList.AddRectFilled(ImVec2(200, 325), ImVec2(400, 330), globeColor, globeColor, globeColor, globeColor)
    drawList.AddRectFilled(ImVec2(200, 297), ImVec2(400, 303), globeColor, globeColor, globeColor, globeColor)
    drawList.AddRectFilled(ImVec2(200, 275), ImVec2(400, 270), globeColor, globeColor, globeColor, globeColor)
    drawList.AddRectFilled(ImVec2(200, 245), ImVec2(400, 250), globeColor, globeColor, globeColor, globeColor)
    drawList.AddRectFilled(ImVec2(220, 225), ImVec2(380, 230), globeColor, globeColor, globeColor, globeColor)
    curval += 1.5
    
    local bounds = 260
    local curVal0 = curval % bounds;
    local curVal1 = (curval + 50) % bounds;
    local curVal2 = (curval + 100) % bounds;
    local curVal3 = (curval + 150) % bounds;
    local curVal4 = (curval + 200) % bounds;
    local curVPos0 = 295 + (curval % bounds) - 125;
    local curVPos1 = 295 + ((curval + 50) % bounds) - 125;
    local curVPos2 = 295 + ((curval + 100) % bounds) - 125;
    local curVPos3 = 295 + ((curval + 150) % bounds) - 125;
    local curVPos4 = 295 + ((curval + 200) % bounds) - 125;
    
    local curThc0 = (curVal0 - 130) / 35.0
    local curThc1 = (curVal1 - 130) / 35.0
    local curThc2 = (curVal2 - 130) / 35.0
    local curThc3 = (curVal3 - 130) / 35.0
    local curThc4 = (curVal4 - 130) / 35.0

    local curVPos10 = curVPos0 - curThc0
    local curVPos11 = curVPos1 - curThc1
    local curVPos12 = curVPos2 - curThc2
    local curVPos13 = curVPos3 - curThc3
    local curVPos14 = curVPos4 - curThc4

    
    local p2y = 230;
    local p3y = 370;

    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos0, p2y), ImVec2(curVPos0, p3y), ImVec2(300, 395), globeColor, 5)
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos1, p2y), ImVec2(curVPos1, p3y), ImVec2(300, 395), globeColor, 5)
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos2, p2y), ImVec2(curVPos2, p3y), ImVec2(300, 395), globeColor, 5)
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos3, p2y), ImVec2(curVPos3, p3y), ImVec2(300, 395), globeColor, 5)
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos4, p2y), ImVec2(curVPos4, p3y), ImVec2(300, 395), globeColor, 5)
    
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos10, p2y), ImVec2(curVPos10, p3y), ImVec2(300, 395), 0xff888888, fabs(curThc0))
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos11, p2y), ImVec2(curVPos11, p3y), ImVec2(300, 395), 0xff888888, fabs(curThc1))
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos12, p2y), ImVec2(curVPos12, p3y), ImVec2(300, 395), 0xff888888, fabs(curThc2))
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos13, p2y), ImVec2(curVPos13, p3y), ImVec2(300, 395), 0xff888888, fabs(curThc3))
    drawList.AddBezierCubic(ImVec2(300, 205),ImVec2(curVPos14, p2y), ImVec2(curVPos14, p3y), ImVec2(300, 395), 0xff888888, fabs(curThc4))
    

    drawList.PushColor(0xff101010)

    drawList.PathLineTo(ImVec2(400, 200), 0xff101010)
    drawList.PathArcTo(ImVec2(300, 300), 90, 0, -PI)
    drawList.PathLineTo(ImVec2(200, 200), 0xff101010)
    drawList.PathFillConcave()
    drawList.PathLineTo(ImVec2(200, 400), 0xff101010)
    drawList.PathArcTo(ImVec2(300, 300), 90, PI, 0)
    drawList.PathLineTo(ImVec2(400, 400), 0xff101010)
    drawList.PathFillConcave()

    drawList.PathLineTo(ImVec2(210, 300), 0xff101010)
    drawList.PathLineTo(ImVec2(200, 200), 0xff101010)
    drawList.PathLineTo(ImVec2(200, 400), 0xff101010)
    drawList.PathFillConcave()

    drawList.PathLineTo(ImVec2(400, 400), 0xff101010)
    drawList.PathLineTo(ImVec2(400, 200), 0xff101010)
    drawList.PathLineTo(ImVec2(390, 300), 0xff101010)
    drawList.PathFillConcave()
    drawList.PopColor()*/

    //drawList.DrawBird(0xff403e35, ImVec2(300, 190), 3)
}
















