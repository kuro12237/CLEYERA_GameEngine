local data = {
    hp = 100,
    attack = 9.0,
    speed = 1.4
}

function GetStageFileName(index)
    local string = {
        [0] = "string : error",
        [1] = "string : 1",
        [2] = "string : 2",
        [3] = "string : 3",
        [4] = "string : 4",
        [5] = "string : 5"
    }

    return string[index] or "string : error" --これは関数のreturn
end

return data --これは最後のreturn


--[[
Luaはreturnを書いたら
終わりだから、基本returnは一つ
dataとかを返したいなら最後に返す

複数データがある場合は
以下のようにまとめてreturnの中に入れる

return {
    Data1 = Data1,
    Data2 = Data2,
    Data3 = Data3,
    Data4 = Data4
}

]]