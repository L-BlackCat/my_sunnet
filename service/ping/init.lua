
local service_id

local isNeedClose

function OnInit(id)
    print("[lua] ping onInit,id:"..id);
    service_id = id;
end


function OnExit()
    print("[lua] ping OnExit "..service_id);
end


function OnServiceMsg(source,buff)
    print("[lua] ping OnServiceMsg id:"..service_id.." msg:"..buff);

    
    if string.len(buff) > 7 then
        int succ = my_sunnet.KillService(service_id);
        if succ > 0 then
            isNeedClose = 1;
        return;
        print("[lua] ping kill over");
    
        return
    end

    my_sunnet.Send(service_id,source,buff.."i");

    print("[lua] ping OnserverMsg over");
end


function close()
    
end
