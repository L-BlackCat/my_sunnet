-- print("[lua] enter")

function OnInit(id)
    print("[lua] main OnInit id:"..id)
    local ping1 = my_sunnet.NewService("ping");
    local ping2 = my_sunnet.NewService("ping");
    local pong = my_sunnet.NewService("ping");

    my_sunnet.Send(ping1,pong,"hello");
    -- my_sunnet.Send(ping2,pong,"hello");
end


function OnExit()
    print("[lua] main OnExit")
end


function OnServiceMsg(source,buff)
    print("[lua] main OnServiceMsg id:"..id);
end


