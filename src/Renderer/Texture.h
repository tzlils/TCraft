class Texture {
    public:
        Texture(const char* path);
        void bind();
        void unbind();
    private:
        unsigned int texture;
};