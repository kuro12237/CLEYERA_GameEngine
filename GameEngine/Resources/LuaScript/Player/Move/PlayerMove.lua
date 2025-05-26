PlayerMove = {
    -- 入力スティックのデッドゾーン（0.0〜1.0）
    LStickDeadZone = 0.15,

    -- 最大移動速度
    maxSpeed = 2.0,

    -- 慣性（0:即時反映 〜 1:非常に滑らか）
    inertiaFactor = 1.0,

    -- 方向転換時の最低速度スケール（0.0〜1.0）
    minSpeedScale = 0.3,

    -- 姿勢補間率（回転角補間用）
    rotateLerp = 0.1,
}

return {
    PlayerMove = PlayerMove,
}
