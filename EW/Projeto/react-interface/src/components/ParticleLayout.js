import { useCallback } from "react";
import Particles from "react-tsparticles";
import { loadFull } from "tsparticles";


function ParticleLayout(){
    const particlesInit = useCallback(async engine => {
        console.log(engine);
        // you can initiate the tsParticles instance (engine) here, adding custom shapes or presets
        // this loads the tsparticles package bundle, it's the easiest method for getting everything ready
        // starting from v2 you can add only the features you need reducing the bundle size
        await loadFull(engine);
    }, []);

    const particlesLoaded = useCallback(async container => {
        await console.log(container);
    }, []);

    return (
        <Particles
            id="tsparticles"
            init={particlesInit} 
            loaded={particlesLoaded}
            options={{
                smooth: true,
                particles: {
                    number: {
                        value: 80,
                        density: {
                            enable: true,
                        },
                    },
                    color: {
                        value: "#ffffff",
                    },
                    shadow: {
                        enable: true,
                        color: "#000000",
                        blur: 5,
                        offset: {
                            x: 3,
                            y: 3,
                        },
                    },
                    shape: {
                        type: "circle",
                    },
                    opacity: {
                        value: 0.5,
                    },
                    size: {
                        value: {
                            min: 1,
                            max: 5,
                        },
                    },
                    links: {
                        enable: true,
                        distance: 150,
                        color: "#ffffff",
                        opacity: 0.4,
                        width: 1,
                        shadow: {
                            enable: true,
                            blur: 5,
                            color: "#000000",
                        },
                    },
                    move: {
                        enable: true,
                        speed: 2,
                    },
                },
                interactivity: {
                    events: {
                        onHover: {
                            enable: true,
                            mode: "repulse",
                            parallax: {
                                enable: false,
                                force: 60,
                                smooth: 10,
                            },
                        },
                        onClick: {
                            enable: true,
                            mode: "push",
                        },
                    },
                    modes: {
                        grab: {
                            distance: 400,
                            links: {
                                opacity: 1,
                            },
                        },
                        bubble: {
                            distance: 400,
                            size: 40,
                            duration: 2,
                            opacity: 0.8,
                        },
                        repulse: {
                            distance: 200,
                        },
                        push: {
                            quantity: 4,
                        },
                        remove: {
                            quantity: 2,
                        },
                    },
                },
                background: {
                    color: "#1a1a1a",
                }
            }}
        />
    );
};

export default ParticleLayout;