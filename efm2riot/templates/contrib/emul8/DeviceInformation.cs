//
// Copyright (c) Antmicro
// Copyright (c) Bas Stottelaar <basstottelaar@gmail.com>
//
// This file is part of the Emul8 project.
// Full license details are defined in the 'LICENSE' file.
//
using Emul8.Logging;
using Emul8.Peripherals.Bus;

namespace Emul8.Peripherals
{
    [AllowedTranslations(AllowedTranslation.ByteToDoubleWord)]
    public class {{ family|upper }}DeviceInformation: IDoubleWordPeripheral, IKnownSize
    {
        public {{ family|upper }}DeviceInformation(ushort deviceNumber, ushort flashSize, ushort sramSize, byte productRevision = 0)
        {
            this.flashSize = flashSize;
            this.sramSize = sramSize;
            this.productRevision = productRevision;
            this.deviceFamily = {{ devinfo.family_id|hex }};
            this.deviceNumber = deviceNumber;
        }

        public void Reset()
        {
        }

        public uint ReadDoubleWord(long offset)
        {
            switch((DeviceInformationOffset)offset)
            {
            {% strip 2 %}
                {% if devinfo.registers|select(name='^EUI48(H|L)+$') %}
                    case DeviceInformationOffset.EUI48L:
                        return (uint)(EUI >> 32);
                    case DeviceInformationOffset.EUI48H:
                        return (uint)(EUI & 0xFFFFFFFF);
                {% endif %}
            {% endstrip %}
            case DeviceInformationOffset.UNIQUEL:
                return (uint)(Unique >> 32);
            case DeviceInformationOffset.UNIQUEH:
                return (uint)(Unique & 0xFFFFFFFF);
            case DeviceInformationOffset.MSIZE:
                return (uint)((sramSize << 16) | (flashSize & 0xFFFF));
            case DeviceInformationOffset.PART:
                return (uint)((productRevision << 24) | ((byte)deviceFamily << 16) | deviceNumber);
            {% strip 2 %}
                {% if devinfo.registers|select(name='^DEVINFOREV$') %}
                    case DeviceInformationOffset.DEVINFOREV:
                        return 0xFFFFFF00 | 0x01;
                {% endif %}
            {% endstrip %}
            default:
                this.LogUnhandledRead(offset);
                return 0;
            }
        }

        public void WriteDoubleWord(long offset, uint value)
        {
            this.LogUnhandledWrite(offset, value);
        }

        public long Size
        {
            get
            {
                return {{ devinfo.size|hex }};
            }
        }

        {% strip 2 %}
            {% if devinfo.registers|select(name='^EUI48(H|L)+$') %}
                public ulong EUI { get; set; }
            {% endif %}
        {% endstrip %}
        public ulong Unique { get; set; }

        private readonly ushort flashSize;
        private readonly ushort sramSize;
        private readonly byte productRevision;
        private readonly byte deviceFamily;
        private readonly ushort deviceNumber;

        // This structure should resemble the structure of {{ family }}_devinfo.h.
        private enum DeviceInformationOffset : long
        {
            {% strip 2 %}
                {% for register in devinfo.registers %}
                    {{ register.name|align(16) }} = {{ register.offset|hex(3) }}, // {{ register.description }}
                {% endfor %}
            {% endstrip %}
        }
    }
}
