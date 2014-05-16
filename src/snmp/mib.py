from pysnmp.entity.rfc3413.oneliner import cmdgen

cmdGen = cmdgen.CommandGenerator()

errorIndication, errorStatus, errorIndex, varBinds = cmdGen.getCmd(
    cmdgen.CommunityData('dhA5gEet'),
    cmdgen.UdpTransportTarget(('10.255.4.103', 161)),
    cmdgen.MibVariable('SNMPv2-MIB', 'sysDescr', 0),
    lookupNames=True, lookupValues=True
)

# Check for errors and print out results
if errorIndication:
    print(errorIndication)
elif errorStatus:
    print(errorStatus)
else:
    for name, val in varBinds:
        print('%s = %s' % (name.prettyPrint(), val.prettyPrint()))
