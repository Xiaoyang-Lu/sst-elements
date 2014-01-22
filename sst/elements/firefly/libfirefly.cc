// Copyright 2009-2013 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2013, Sandia Corporation
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.


#include <sst_config.h>
#include <sst/core/component.h>
#include <sst/core/element.h>

#include <ioSwitch.h>
#include <nic.h>
#include <testDriver.h>
#include <nicTester.h>
#include <hades.h>
#include <simpleIO.h>
#include <merlinIO.h>
#include <funcSM/init.h>
#include <funcSM/fini.h>
#include <funcSM/rank.h>
#include <funcSM/size.h>
#include <funcSM/alltoallv.h>
#include <funcSM/barrier.h>
#include <funcSM/allreduce.h>
#include <funcSM/allgather.h>
#include <funcSM/gatherv.h>
#include <funcSM/recv.h>
#include <funcSM/send.h>
#include <funcSM/wait.h>
#include <funcSM/waitAny.h>
#include <funcSM/waitAll.h>
#include <ctrlMsg.h>
#include <longMsgProtocol.h>
#include <merlinEvent.h>

using namespace Firefly;


BOOST_CLASS_EXPORT(MerlinFireflyEvent)

static SST::Component*
create_ioSwitch(SST::ComponentId_t id, SST::Params& params)
{
    return new IOSwitch( id, params );
}

static SST::Component*
create_nicTester(SST::ComponentId_t id, SST::Params& params)
{
    return new NicTester( id, params );
}

static Module* 
load_nic(Component* comp, Params& params)
{
    return new Nic( comp, params );
}

static SST::Component*
create_testDriver(SST::ComponentId_t id, SST::Params& params)
{
    return new TestDriver(id, params);
}

static Module*
load_hades(Component* comp, Params& params)
{
    return new Hades(comp, params);
}

static Module*
load_simpleIO(Params& params)
{
    return new SimpleIO(params);
}

static Module*
load_merlinIO(Component* comp, Params& params)
{
    return new MerlinIO(comp, params);
}

static Module*
load_hermesInitSM(Params& params)
{
    return new InitFuncSM(params);
}

static Module*
load_hermesFiniSM(Params& params)
{
    return new FiniFuncSM(params);
}

static Module*
load_hermesRankSM(Params& params)
{
    return new RankFuncSM(params);
}

static Module*
load_hermesSizeSM(Params& params)
{
    return new SizeFuncSM(params);
}

static Module*
load_hermesAlltoallvSM(Params& params)
{
    return new AlltoallvFuncSM(params);
}

static Module*
load_hermesBarrierSM(Params& params)
{
    return new BarrierFuncSM(params);
}

static Module*
load_hermesAllreduceSM(Params& params)
{
    return new AllreduceFuncSM(params);
}

static Module*
load_hermesAllgatherSM(Params& params)
{
    return new AllgatherFuncSM(params);
}

static Module*
load_hermesGathervSM(Params& params)
{
    return new GathervFuncSM(params);
}

static Module*
load_hermesRecvSM(Params& params)
{
    return new RecvFuncSM(params);
}

static Module*
load_hermesSendSM(Params& params)
{
    return new SendFuncSM(params);
}

static Module*
load_hermesWaitSM(Params& params)
{
    return new WaitFuncSM(params);
}

static Module*
load_hermesWaitAnySM(Params& params)
{
    return new WaitAnyFuncSM(params);
}

static Module*
load_hermesWaitAllSM(Params& params)
{
    return new WaitAllFuncSM(params);
}

static Module*
load_ctrlMsgProtocol( Component* comp, Params& params )
{
    return new CtrlMsg( comp, params );
}

static Module*
load_LongMsgProtocol( Component* comp, Params& params )
{
    return new LongMsgProtocol( comp, params );
}

static void init_MerlinFireflyEvent()
{
}

static const ElementInfoComponent components[] = {
    { "ioSwitch",
      "Firefly IO Switch",
      NULL,
      create_ioSwitch,
    },
    { "testDriver",
      "Firefly test driver ",
      NULL,
      create_testDriver,
    },
    { "nicTester",
      "nic tester",
      NULL,
      create_nicTester,
    },
    { NULL, NULL, NULL, NULL }
};

static const ElementInfoModule modules[] = {
    { "hades",
      "Firefly Hermes module",
      NULL,
      NULL,
      load_hades,
      NULL,
    },
    { "testIO",
      "Firefly IO module",
      NULL,
      load_simpleIO,
      NULL,
    },
    { "nic",
      "Nic module",
      NULL,
      NULL,
      load_nic,
      NULL,
    },
    { "merlinIO",
      "Merlin IO module",
      NULL,
      NULL,
      load_merlinIO,
      NULL,
    },
    { "Init",
      "Hermes Init Function State Machine",
      NULL,
      load_hermesInitSM,
      NULL,
    },
    { "Fini",
      "Hermes Fini Function State Machine",
      NULL,
      load_hermesFiniSM,
      NULL,
    },
    { "Rank",
      "Hermes Rank Function State Machine",
      NULL,
      load_hermesRankSM,
      NULL,
    },
    { "Size",
      "Hermes Size Function State Machine",
      NULL,
      load_hermesSizeSM,
      NULL,
    },
    { "Alltoall",
      "Hermes Alltoallv Function State Machine",
      NULL,
      load_hermesAlltoallvSM,
      NULL,
    },
    { "Barrier",
      "Hermes Barrier Function State Machine",
      NULL,
      load_hermesBarrierSM,
      NULL,
    },
    { "Allreduce",
      "Hermes Allreduce Function State Machine",
      NULL,
      load_hermesAllreduceSM,
      NULL,
    },
    { "Reduce",
      "Hermes Reduce Function State Machine",
      NULL,
      load_hermesAllreduceSM,
      NULL,
    },
    { "Allgather",
      "Hermes Allgather Function State Machine",
      NULL,
      load_hermesAllgatherSM,
      NULL,
    },
    { "Allgatherv",
      "Hermes Allgatherv Function State Machine",
      NULL,
      load_hermesAllgatherSM,
      NULL,
    },
    { "Gatherv",
      "Hermes Gatherv Function State Machine",
      NULL,
      load_hermesGathervSM,
      NULL,
    },
    { "Gather",
      "Hermes Gather Function State Machine",
      NULL,
      load_hermesGathervSM,
      NULL,
    },
    { "Alltoallv",
      "Hermes Alltoallv Function State Machine",
      NULL,
      load_hermesAlltoallvSM,
      NULL,
    },
    { "Irecv",
      "Hermes Irecv Function State Machine",
      NULL,
      load_hermesRecvSM,
      NULL,
    },
    { "Isend",
      "Hermes Isend Function State Machine",
      NULL,
      load_hermesSendSM,
      NULL,
    },
    { "Recv",
      "Hermes Recv Function State Machine",
      NULL,
      load_hermesRecvSM,
      NULL,
    },
    { "Send",
      "Hermes Send Function State Machine",
      NULL,
      load_hermesSendSM,
      NULL,
    },
    { "Wait",
      "Hermes Wait Function State Machine",
      NULL,
      load_hermesWaitSM,
      NULL,
    },
    { "WaitAny",
      "Hermes WaitAny Function State Machine",
      NULL,
      load_hermesWaitAnySM,
      NULL,
    },
    { "WaitAll",
      "Hermes WaitAll Function State Machine",
      NULL,
      load_hermesWaitAllSM,
      NULL,
    },
    { "CtrlMsg",
      "CtrlMsg protocol",
      NULL,
      NULL,
      load_ctrlMsgProtocol,
      NULL,
    },
    { "LongMsgProto",
      "Long Message Pootocol",
      NULL,
      NULL,
      load_LongMsgProtocol,
      NULL,
    },
    { NULL, NULL, NULL, NULL, NULL }
};

static const ElementInfoEvent events[] = { 
    { "MerlinFireflyEvent",
      "MerlinFireflyEvent",
        NULL,
        init_MerlinFireflyEvent 
    },
    { NULL, NULL, NULL, NULL}
};

extern "C" {
    ElementLibraryInfo firefly_eli = {
        NULL,
        NULL, 
        components,
        events,
        NULL,
        modules,
        NULL,
        NULL,
    };
}
